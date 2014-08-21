#include <stdio.h>
#include "libim/core.h"
#include "libim/connection.h"
#include "util/error_process.h"
#include "mconn.h"
#include "util/workq.h"

static void connect_progress(im_connection* conn, const char* text, size_t current_step, size_t step_count) {
	
}
static void connected(im_connection* conn) {
	
}
static void disconnected(im_connection* conn) {
	printf("connected %s:%s\n", conn->_host.c_str(), conn->_serv.c_str());
}
static void notice(im_connection* conn, const char* text) {
	
}
static void network_connected(im_connection* conn) {
	printf("connected %s:%s\n", conn->_host.c_str(), conn->_serv.c_str());
}
static void network_disconnected(im_connection* conn) {
	
}
static void report_disconnect(im_connection *gc, const char *text) {
	
}
static void network_error(im_connection* conn, int err) {
	int n = err;
	printf("connect error:%s", errno2msg(err).c_str());
}
static void can_read(im_connection* conn) {
	char buf[1024] = {0};
	conn->read(buf, 1023);
	printf("%s", buf);
}


static void connect_cb(im_connection* conn) {
	if (conn->_state == LIBIM_DISCONNECTED) {
		// 销毁客户端。用户重新登录时，会再次新建
		conn->_proto_data = NULL;
	}
	if (conn->_state == LIBIM_CONNECTED) {
		conn->write("hello wrold", 12);
	}
}

static im_connection_event_process event_proc = 
{
	connect_cb,
	can_read
};



static im_connection_ui_ops ops =
{
	NULL,
	NULL,
	NULL,
	NULL,
	network_connected,
	network_disconnected,
	NULL,
	network_error
};

im_connection conn;

void test_conn()
{
	im_connection::set_ui_ops(&ops);
	conn.set_event_process(&event_proc);
	conn.connect("172.16.100.223", "7732");
	
	im_connection::dispatch();

	int n = 3;
	while (n--) {
		//conn.write("hello", 5);
		Sleep(1000);
	}

	im_connection::exit_dispatch();
}