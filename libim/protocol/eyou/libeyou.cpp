#include "eyou.h"
#include "protocol_plugin.h"
#include "account.h"
#include "connection.h"
#include "exstring.h"
#include "iq.h"
#include <windows.h>

static void can_read(im_connection* conn) {
	char buf[1024];
	conn->read(buf, 1023);
}
static void connect_cb(im_connection* conn) {
	eyou* e = (eyou*)conn->_proto_data;

	if (conn->_state == LIBIM_DISCONNECTED) {
		// 销毁客户端。用户重新登录时，会再次新建
		delete e;
		conn->_proto_data = NULL;
	}
	if (conn->_state == LIBIM_CONNECTED) {
		// 连接成功，开始登录
		eyou_iq iq;
		iq._id = "101";
		iq._method = "auth";
		
		conn->write();
	}
}

static im_connection_event_process event_proc = 
{
	connect_cb,
	can_read
};

static void eyou_login(im_account* acc)
{
	im_connection* conn = acc->get_connection();
	// 创建一个eyou客户端
	eyou* e = new eyou();
	conn->_proto_data = e;

	conn->set_event_process(&event_proc);

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
	eyou_logout
};

static void init_plugin()
{
	protocol_plugin::regist_plugin("eyouim", &imp);
}

AUTO_REGIST_PLUGIN_BEFOR_APPRUN(init_plugin)