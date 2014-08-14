#ifndef ___LIBIM_CONVERSATION__H__
#define ___LIBIM_CONVERSATION__H__

#include "value.h"

class im_conversation;
class im_account;

typedef enum 
{
	LIBIM_MESSAGE_SEND		= 0x0001,
	LIBIM_MESSAGE_RECV		= 0x0002,
} im_message_flags;

struct _im_conversation_ui_ops
{
	void (*create_conversation)(im_conversation* conv);
	void (*destroy_conversation)(im_conversation* conv);
	void (*receive_chat)(im_conversation* conv, const char* who,
						const char* content, im_message_flags flags, time_t mtime);
};

class im_conversation
{
	int					_type;
	im_account*			_account;
	std::string			_title;
	std::string			_name;
	void*				_uidata;
	_im_conversation_ui_ops* _ops;
};


#endif