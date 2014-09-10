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

bool im_account::is_connected() {
	return _connection && (_connection->_state == LIBIM_CONNECTED);
}
bool im_account::is_connecting() {
	return _connection && (_connection->_state == LIBIM_CONNECTING);
}
bool im_account::is_disconnected() {
	return (_connection == NULL) || (_connection->_state == LIBIM_DISCONNECTED);
}


void im_account::disconnect()
{
	_connection->disconnect();
	delete _connection;
	_connection = NULL;
}

void im_account::connect_server()
{
	_imp = protocol_plugin::find_plugin(_protocal_name.c_str());
	if (!_imp) {
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

	_imp->login(this);
}

bool im_account::load_from_config(const char* config_path)
{
	return _settings.read_file(config_path);
}
bool im_account::save_to_config(const char* config_path)
{
	_settings.set_string("username", _username.c_str());
	_settings.set_string("password", _password.c_str());
	_settings.set_string("alias", _alias.c_str());
	_settings.set_string("protocal", _protocal_name.c_str());

	return _settings.save_file(config_path);
}

/**
 * �û����á�
 * key : type : ���� 
 *
 * gender : bool : ��Ϊtrue��ŮΪfalse
 * mood : string : ����
 * buddy_icon_path : string : �û�ͼƬ������ͷ��
 * protocal : string : Э������
 * username : string : �û�uid
 * password : string : �û����루����֮������ģ�
 * alias : string : �������ǳ�
 */
std::string im_account::get_config_string(const char* k, const char* default_value) {
	return _settings.get_string(k, default_value);
}
int im_account::get_config_int(const char* k, int default_value) {
	return _settings.get_int(k, default_value);
}
bool im_account::get_config_bool(const char* k, bool default_value) {
	return _settings.get_bool(k, default_value);
}
void im_account::set_config_string(const char* k, const char* val) {
	return _settings.set_string(k, val);
}
void im_account::set_config_int(const char* k, int val) {
	return _settings.set_int(k, val);
}
void im_account::set_config_bool(const char* k, bool val) {
	return _settings.set_bool(k, val);
}
