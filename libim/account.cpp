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
		// TODO:请求用户输入密码
		error_quit("No password!");
		return;
	}

	// 为登录创建一个新的链接
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
 * 用户配置。
 * key : type : 含义 
 *
 * gender : bool : 男为true，女为false
 * mood : string : 心情
 * buddy_icon_path : string : 用户图片，或者头像
 * protocal : string : 协议名称
 * username : string : 用户uid
 * password : string : 用户密码（加密之后的密文）
 * alias : string : 别名，昵称
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
