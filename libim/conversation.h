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
	/* 构造放入私有，防止外部直接构造
	 * 构造新的对象，请使用make_new
	 * 析构对象，使用remove
	 */ 
	im_conversation();

	/* 一旦构造，禁止修改，name作为hash表的key。不能轻易改动
	 * 这变量不是给界面显示用的。显示请用title
	 */
	std::string			_name;
	/* hash键，不能轻易修改 */
	im_conversation_type _type;
public:

	im_account*			_account;

	/* 标题，界面可能会用到。也可修改 */
	std::string			_title;

	/* 会话中的成员列表 */
	im_list				_members;
	/* 存储了conversation在生存期内的消息记录 im_conversation_message */
	im_list				_history;

	void				send_message(const char* who, const char* content, im_message_flags flags, time_t mtime);

	static void			init();
	static void			uninit();

	static im_conversation* make_conversation(im_account* acc, const char* conv_name, im_conversation_type type);
	static im_conversation* find_conversation(im_account* acc, const char* conv_name, im_conversation_type type);
	static void			remove_conversation(im_conversation* conv);

	static void			set_ui_ops(im_conversation_ui_ops* ops);
	static im_conversation_ui_ops* get_ui_ops();
};


#endif