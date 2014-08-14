#ifndef ___LIBIM_ACCOUNT__H__
#define ___LIBIM_ACCOUNT__H__

#include "value.h"

class im_connection;

class im_account
{
	char*			username;
	char*			alias;
	char*			password;
	char*			userinfo;
	char*			buddy_icon_path;
	bool			remember_pass;

	im_connection*	connection;
	std::hash_map<std::string, std::string> settings;

public:
	const char*		get_username() {return username;}
	im_connection*	get_connection() {return connection;}

	bool			is_connected();
	bool			is_connecting();
	bool			is_disconnected();

	// settings
	const char*		get_conf_string(const char* name, const char* default_value);
	int				get_conf_int(const char* name, int default_value);
	bool			get_conf_bool(const char* name, bool default_value);
	void			set_conf_string(const char* name, const char* value);
	void			set_conf_int(const char* name, int value);
	void			set_conf_bool(const char* name, bool value);
};


#endif