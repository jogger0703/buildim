#ifndef ___LIBIM_CONNECTION__H__
#define ___LIBIM_CONNECTION__H__

#include "value.h"

class im_account;
class im_connection;

typedef enum
{
    LIBIM_CONNECTION_HTML       = 0x0001, /**< Connection sends/receives in 'HTML'. */
    LIBIM_CONNECTION_NO_BGCOLOR = 0x0002, /**< Connection does not send/receive
                               background colors.                  */
    LIBIM_CONNECTION_AUTO_RESP  = 0x0004,  /**< Send auto responses when away.       */
    LIBIM_CONNECTION_FORMATTING_WBFO = 0x0008, /**< The text buffer must be formatted as a whole */
    LIBIM_CONNECTION_NO_NEWLINES = 0x0010, /**< No new lines are allowed in outgoing messages */
    LIBIM_CONNECTION_NO_FONTSIZE = 0x0020, /**< Connection does not send/receive font sizes */
    LIBIM_CONNECTION_NO_URLDESC = 0x0040,  /**< Connection does not support descriptions with links */
    LIBIM_CONNECTION_NO_IMAGES = 0x0080,  /**< Connection does not support sending of images */
    LIBIM_CONNECTION_ALLOW_CUSTOM_SMILEY = 0x0100, /**< Connection supports sending and receiving custom smileys */
    LIBIM_CONNECTION_SUPPORT_MOODS = 0x0200, /**< Connection supports setting moods */
    LIBIM_CONNECTION_SUPPORT_MOOD_MESSAGES = 0x0400 /**< Connection supports setting a message on moods */
} im_connection_flags;

typedef enum {
	LIBIM_DISCONNECTED = 0,
	LIBIM_CONNECTED,
	LIBIM_CONNECTING
} im_connection_state;

typedef struct
{
	/** 
	 * 连接处理步进
	 * @参考im_connection::update_progress
	 */
	void (*connect_progress)(im_connection* conn, const char* text, size_t current_step, size_t step_count);
	void (*connected)(im_connection* conn);
	void (*disconnected)(im_connection* conn);
	void (*notice)(im_connection* conn, const char* text);
	void (*network_connected)(im_connection* conn);
	void (*network_disconnected)(im_connection* conn);
	void (*report_disconnect)(im_connection *conn, const char *text);
	void (*network_error)(im_connection* conn, int err);
} im_connection_ui_ops;

class im_connection
{
public:
	im_connection_ui_ops* _ops;
	im_account*			_account;
	im_connection_flags	_flags;
	im_connection_state _state;
	void*				_proto_data;
	char*				_password;
	std::string			_host;
	std::string			_serv; // port or serv name
	__int32				_fd;
	

	void				set_ui_ops(im_connection_ui_ops* ops);
	void				set_account(im_account* account);

	/** 
	 * 刷新处理步进
	 * @text 单步中附带的信息，例如“正在获取权限” “正在同步用户状态”
	 * @current_step 当前步进
	 * @step_count 总步进
	 */
	void				update_progress(const char *text, size_t step, size_t count);

	/** 
	 * 通知上层，连接的信息
	 */
	void				notice(const char* text);

	void				error_occured(const char* reason);

	void				connect(const char* host, const char* serv);
	void				disconnect(void);

	int					write(const char* buf, int len);
	int					read(char* buf, int max_len);
};


#endif