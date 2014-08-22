#ifndef ___LIBIM_CONVERSATION__H__
#define ___LIBIM_CONVERSATION__H__

#include "value.h"
#include "account.h"
#include "connection.h"

class im_conversation;
class im_account;

typedef enum 
{
	LIBIM_MESSAGE_SEND		= 0x0001,
	LIBIM_MESSAGE_RECV		= 0x0002,
} im_message_flags;

typedef enum {
	LIBIM_CONV_TYPE_UNKNOWN = 0,
	LIBIM_CONV_TYPE_SINGLE,
	LIBIM_CONV_TYPE_ROOM,
	LIBIM_CONV_TYPE_MAIL
} im_conversation_type;

class im_conversation_message
{
	std::string		_who_sent;
	std::string		_content;
	im_message_flags _flags;
};

typedef struct 
{
	void (*create_conversation)(im_conversation* conv);
	void (*destroy_conversation)(im_conversation* conv);
	void (*receive_message)(im_conversation* conv, const char* who,
						const char* content, im_message_flags flags, time_t mtime);
} im_conversation_ui_ops;

class im_conversation
{
public:
	im_account*			_account;
	im_connection*		_connection;

	im_conversation_type _type;
	std::string			_title;
	std::string			_name;

	/* 会话中的成员列表 */
	im_list				_members;
	/* 存储了conversation在生存期内的消息记录 im_conversation_message */
	im_list				_history;

	static void			init();
	static void			uninit();

	static void			set_ui_ops(im_conversation_ui_ops* ops);
	static im_conversation_ui_ops* get_ui_ops();
};


#endif