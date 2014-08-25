#include "connection.h"
#include "util/network.h"
#include "event2/bufferevent.h"
#include "event2/buffer.h"
#include "event2/listener.h"
#include "event2/util.h"
#include "event2/event.h"
#include "util/workq.h"

#pragma comment(lib, "libevent.lib")
#pragma comment(lib, "libevent_core.lib")
#pragma comment(lib, "libevent_extras.lib")

// libevent instance
static struct event_base *base = NULL;
static bool libevent_quit = true;
// 用于支持libevent工作的线程池
static WorkQ libevent_wq;
// ui回调是所有链接共享的。一次设置，全部生效
static im_connection_ui_ops* _ops;


static void write_cb(evutil_socket_t sock, short flags, void * args)
{
	im_connection* conn = (im_connection*)args;

	if (evbuffer_get_length(conn->_out) > 0)
		evbuffer_write(conn->_out, conn->_fd);
}
static void read_cb(evutil_socket_t sock, short flags, void * args)
{
	im_connection* conn = (im_connection*)args;
	if (conn->_events && conn->_events->can_read)
		conn->_events->can_read(conn);
}
static void timer_cb(evutil_socket_t fd, short what, void *arg)
{
	im_connection* conn = (im_connection*)arg;
	if (conn->_events && conn->_events->on_timer) {
		conn->_events->on_timer(conn);
	}
}

void im_connection::init()
{
	base = event_base_new();
}
void im_connection::uninit()
{
	if (base)
		event_base_free(base);
	base = NULL;
}

void im_connection::set_ui_ops(im_connection_ui_ops* ops) {
	_ops = ops;
}
im_connection_ui_ops* im_connection::get_ui_ops(void) {
	return _ops;
}

void im_connection::set_event_process(im_connection_event_process* proc) {
	_events = proc;
}
im_connection_event_process* im_connection::get_event_process(void) {
	return _events;
}

void im_connection::set_account(im_account* account) {
	_account = account;
}

/**
 * 设置心跳包触发器
 * @second 时间间隔，以秒为单位
 */
void im_connection::set_keep_alive_idle(int second)
{
	struct timeval idle = { second, 0 };

	_timer = event_new(base, -1, EV_PERSIST, timer_cb, (void*)this);
    event_add(_timer, &idle);
}

void im_connection::connect(const char* host, const char* serv)
{
	_host = host;
	_serv = serv;
	_state = LIBIM_DISCONNECTED;
	_fd = tcp_connect(host, serv);
	if (_fd == -1) {
		if (_ops->network_error)
			_ops->network_error(this, getneterror());
		return;
	}

	_state = LIBIM_CONNECTED;

	set_sock_block(_fd, false);

	_re = event_new(base, _fd, EV_READ|EV_PERSIST, read_cb, (void*)this);
	_we = event_new(base, _fd, EV_WRITE|EV_PERSIST, write_cb, (void*)this);
	event_add(_re, NULL);
	event_add(_we, NULL);

	_in = evbuffer_new();
	_out = evbuffer_new();

	if (_events->connect_cb)
		_events->connect_cb(this);

	if (_ops->network_connected)
		_ops->network_connected(this);
}

void im_connection::disconnect(void)
{
	closesocket(_fd);
	evbuffer_free(_in);
	evbuffer_free(_out);
	if (_ops->network_disconnected)
		_ops->network_disconnected(this);
	if (_events->connect_cb)
		_events->connect_cb(this);
}

/** 
 * 只将数据写入缓冲区。当网络层准备好后，会调用write_cb发出数据
 * @buf 待发数据
 * @len 待发数据长度
 * @成功返回数据长度，错误返回-1
 */
int im_connection::write(const char* buf, int len)
{
	if (evbuffer_add(_out, buf, len) != 0)
		return -1;
	return len;
}

/** 
 * 拷贝libevent缓冲区中的数据到指定buf，当缓冲区中有数据之后，会通过can_read函数通知上层
 * @buf 存放数据的缓冲区
 * @max_len 缓冲区的最大长度
 * @返回拷贝的数据长度
 */
int im_connection::read(char* buf, int max_len)
{
	int buflen = peek(buf, max_len);
	if (buflen < 0)
		return -1;

	if (evbuffer_drain(_in, buflen) < 0)
		return -1;
	return buflen;
}

/** 
 * 窥探缓冲区，但不清空
 * 参考read函数
 * 如果@buf为空，则返回缓冲区长度
 */
int im_connection::peek(char* buf, int max_len)
{
	int buflen = evbuffer_get_length(_in);
	if (buflen < max_len) {
		if (evbuffer_read(_in, _fd, max_len-buflen) < 0) {
			if (_ops->network_disconnected)
				_ops->network_disconnected(this);
			return -1;
		}
	}

	if (buf)
		return evbuffer_copyout(_in, buf, max_len);
	else
		return evbuffer_get_length(_in);
}

static int run_dispatch(void* arg)
{
	im_connection* conn = (im_connection*)arg;
	struct timeval ten_sec;

	ten_sec.tv_sec = 0;
	ten_sec.tv_usec = 500;

	while (!libevent_quit) {
		/* This schedules an exit ten seconds from now. */
		event_base_loopexit(base, &ten_sec);
		event_base_dispatch(base);
	}

	return 0;
}

void im_connection::dispatch()
{
	if (!libevent_quit)
		return;

	libevent_quit = false;
	libevent_wq.init(1, 1, 1, run_dispatch);
	libevent_wq.add_work(NULL);
}

void im_connection::exit_dispatch()
{
	if (libevent_quit)
		return;
	libevent_quit = true;
	libevent_wq.destroy();
}