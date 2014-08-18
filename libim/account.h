#ifndef ___LIBIM_ACCOUNT__H__
#define ___LIBIM_ACCOUNT__H__

#include "value.h"
#include "util/config.h"

class im_connection;

class im_account
{
	std::string		username;
	std::string		alias;
	std::string		password;
	std::string		userinfo;
	std::string		buddy_icon_path;
	bool			remember_pass;
	hash_config		settings;

	im_connection*	connection;

public:
	std::string		get_username() {return username;}
	im_connection*	get_connection() {return connection;}

	bool			is_connected();
	bool			is_connecting();
	bool			is_disconnected();

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