#include "account.h"
#include "protocol_plugin.h"
#include "connection.h"
#include "util/error_process.h"

void im_account::connect_server()
{
	protocol_plugin_implement* imp = protocol_plugin::find_plugin(_protocal_name.c_str());
	if (!imp) {
		error_quit("Missing protocol plugin!");
		return;
	}

	if (_password.empty()) {
		// TODO:请求用户输入密码
		error_quit("No password!");
		return;
	}

	imp->login(this);
}