#include "eyou.h"
#include "protocol_plugin.h"
#include "account.h"
#include "connection.h"
#include <windows.h>

static void can_read(im_connection* conn) {
	char buf[1024];
	conn->read(buf, 1023);
}


static im_connection_event_process event_proc = 
{
	can_read
};

static void eyou_login(im_account* acc)
{
	// 为登录创建一个新的链接
	im_connection* conn = new im_connection();
	conn->_account = acc;
	acc->_connection = conn;

	conn->set_event_process(&event_proc);

	conn->connect(acc->_settings.get_string("serverhost", "ims1.eyou.net").c_str(),
				acc->_settings.get_string("serverport", "8100").c_str());

	// 拼装验证包
	

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