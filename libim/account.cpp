#include "account.h"
#include "protocol_plugin.h"
#include "connection.h"
#include "util/error_process.h"


static im_account_ui_ops* _ops = NULL;

void im_account::set_ui_ops(im_account_ui_ops* ops) {
	_ops = ops;
}
im_account_ui_ops* im_account::get_ui_ops(void)
{
	return _ops;
}

void im_account::disconnect()
{
	_connection->disconnect();
	delete _connection;
	_connection = NULL;
}

void im_account::connect_server()
{
	protocol_plugin_implement* imp = protocol_plugin::find_plugin(_protocal_name.c_str());
	if (!imp) {
		error_quit("Missing protocol plugin!");
		return;
	}

	if (_password.empty()) {
		// TODO:�����û���������
		error_quit("No password!");
		return;
	}

	// Ϊ��¼����һ���µ�����
	im_connection* conn = new im_connection();
	conn->_account = this;
	_connection = conn;

	imp->login(this);
}