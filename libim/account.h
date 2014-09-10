#ifndef ___LIBIM_ACCOUNT__H__
#define ___LIBIM_ACCOUNT__H__

#include "value.h"
#include "status.h"
#include "util/config.h"
#include "protocol_plugin.h"

class im_connection;
class im_account;
class im_buddy_node;

typedef struct
{
	/** 
	 * ×´Ì¬¸Ä±ä
	 */
	void (*status_changed)(im_account* account, im_status status);
} im_account_ui_ops;

class im_account
{
	im_connection*	_connection;
	im_status		_current_status;

public:

	protocol_plugin_implement* _imp;
	std::string		_username;
	std::string		_alias;
	std::string		_password;
	std::string		_protocal_name;
	
	hash_config		_settings;

	bool			load_from_config(const char* config_path);
	bool			save_to_config(const char* config_path);

	std::string		get_config_string(const char* k, const char* default_value);
	int				get_config_int(const char* k, int default_value);
	bool			get_config_bool(const char* k, bool default_value);
	void			set_config_string(const char* k, const char* val);
	void			set_config_int(const char* k, int val);
	void			set_config_bool(const char* k, bool val);


	static void		init(void);
	static void		uninit(void);

	static void		set_ui_ops(im_account_ui_ops*);
	static im_account_ui_ops* get_ui_ops(void);
	std::string		get_username() {return _username;}
	im_connection*	get_connection() {return _connection;}

	im_status		get_status() {return _current_status;}
	void			set_status(im_status status) {_current_status = status;}

	bool			is_connected();
	bool			is_connecting();
	bool			is_disconnected();

	void			connect_server();
	void			disconnect();
};


#endif