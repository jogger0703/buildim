#include "connection.h"
#include "util/network.h"
#include "event2/bufferevent.h"
#include "event2/buffer.h"
#include "event2/listener.h"
#include "event2/util.h"
#include "event2/event.h"


void im_connection::set_ui_ops(im_connection_ui_ops* ops) {
	_ops = ops;
}
void im_connection::set_account(im_account* account) {
	_account = account;
}

void im_connection::connect(const char* host, const char* serv)
{
	_host = host;
	_serv = serv;
	_fd = tcp_connect(host, serv);
	if (_fd == -1) {
		if (_ops->network_error)
			_ops->network_error(this, getneterror());
	}
	else {
		if (_ops->network_connected)
			_ops->network_connected(this);
	}
}

void im_connection::disconnect(void)
{
	closesocket(_fd);
	if (_ops->network_disconnected)
		_ops->network_disconnected(this);
}