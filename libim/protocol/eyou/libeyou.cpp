#include "eyou.h"
#include "protocol_plugin.h"
#include "account.h"
#include "connection.h"
#include "exstring.h"
#include "iq.h"
#include "io.h"
#include "message.h"
#include <windows.h>

static void can_read(im_connection* conn) {
	eyou_read_socket(conn);
}

static void on_timer(im_connection* conn) {
	if (conn->_state == LIBIM_CONNECTED) {
		const char* keepalive = "<iq method=\"keepalive\" />";
		conn->write(keepalive, strlen(keepalive));
	}
}

static void connect_cb(im_connection* conn) {
	eyou* e = (eyou*)conn->_proto_data;

	if (conn->_state == LIBIM_DISCONNECTED) {
		// 销毁客户端。用户重新登录时，会再次新建
		delete e;
		conn->_proto_data = NULL;
	}
	if (conn->_state == LIBIM_CONNECTED) {
		DPRINT(LOG_INFO, "connected server %s:%s", conn->_host.c_str(), conn->_serv.c_str());
		e->set_auth_state(EYOU_STATE_CONNECTED);
	}
}

static void eyou_login(im_account* acc)
{
	im_connection* conn = acc->get_connection();
	// 创建一个eyou客户端
	eyou* e = new eyou();
	conn->_proto_data = e;
	e->_account = acc;
	e->_conn = acc->get_connection();

	conn->connect(acc->_settings.get_string("serverhost", "ims1.eyou.net").c_str(),
				acc->_settings.get_string("serverport", "8100").c_str());

	conn->dispatch();
}

static void eyou_logout(im_connection* conn)
{
	conn->disconnect();
}


static protocol_plugin_implement imp =
{
	eyou_login,
	eyou_logout,

	connect_cb,
	can_read,
	on_timer,

	eyou_message::send_chat,
};

static void init_plugin()
{
	protocol_plugin::regist_plugin("eyouim", &imp);
}

AUTO_REGIST_PLUGIN_BEFOR_APPRUN(init_plugin)