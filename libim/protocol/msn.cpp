#include "eyou.h"
#include "protocol_plugin.h"
#include "account.h"
#include "connection.h"
#include <windows.h>


static void eyou_login(im_account* acc)
{
	im_connection* conn = acc->_connection;
	conn->connect(acc->_settings.get_string("serverhost", "ims1.eyou.net").c_str(),
				acc->_settings.get_string("serverport", "8100").c_str());
}


static protocol_plugin_implement imp =
{
	eyou_login,
	NULL
};

static void init_plugin()
{
	protocol_plugin::regist_plugin("eyouim", &imp);
}

AUTO_REGIST_PLUGIN_BEFOR_APPRUN(init_plugin)