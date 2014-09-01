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
	std::string		_mood;
	std::string		_avatar;
	std::string		_gender;
	std::string		_alias;
	std::string		_password;
	std::string		_buddy_icon_path;
	std::string		_protocal_name;
	

	bool			_remember_pass;
	hash_config		_settings;

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