#ifndef ___LIBIM_ACCOUNT__H__
#define ___LIBIM_ACCOUNT__H__

#include "value.h"
#include "util/config.h"

class im_connection;

class im_account
{
public:
	std::string		_username;
	std::string		_alias;
	std::string		_password;
	std::string		_userinfo;
	std::string		_buddy_icon_path;
	std::string		_protocal_name;

	bool			_remember_pass;
	hash_config		_settings;


	im_connection*	_connection;

	std::string		get_username() {return _username;}
	im_connection*	get_connection() {return _connection;}

	bool			is_connected();
	bool			is_connecting();
	bool			is_disconnected();

	void			connect_server();
	// settings
	// 这些函数直接访问成员变量settings.get_string set_string ...
// 	std::string		get_conf_string(const char* name, const char* default_value);
// 	int				get_conf_int(const char* name, int default_value);
// 	bool			get_conf_bool(const char* name, bool default_value);
// 	void			set_conf_string(const char* name, const char* value);
// 	void			set_conf_int(const char* name, int value);
// 	void			set_conf_bool(const char* name, bool value);
};


#endif