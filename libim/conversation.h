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
	/* �������˽�У���ֹ�ⲿֱ�ӹ���
	 * �����µĶ�����ʹ��make_new
	 * ��������ʹ��remove
	 */ 
	im_conversation();

	/* һ�����죬��ֹ�޸ģ�name��Ϊhash���key���������׸Ķ�
	 * ��������Ǹ�������ʾ�õġ���ʾ����title
	 */
	std::string			_name;
	/* hash�������������޸� */
	im_conversation_type _type;
public:

	im_account*			_account;

	/* ���⣬������ܻ��õ���Ҳ���޸� */
	std::string			_title;

	/* �Ự�еĳ�Ա�б� */
	im_list				_members;
	/* �洢��conversation���������ڵ���Ϣ��¼ im_conversation_message */
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