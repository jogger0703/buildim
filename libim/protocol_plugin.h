#ifndef ___LIBIM_PROTOCOL_PLUGIN__H__
#define ___LIBIM_PROTOCOL_PLUGIN__H__

#include "value.h"
#include "conversation.h"

class im_account;
class im_connection;
class protocol_plugin;
class protocol_plugin_register;
class im_conversation;

typedef struct
{
	void (*login)(im_account* acc);
	void (*close)(im_connection* conn);

	void (*connect_cb)(im_connection* conn);
	void (*can_read)(im_connection* conn);
	void (*on_timer)(im_connection* conn);

	void (*send_message_plain)(im_conversation* conv, const char* who, const char* content, im_message_flags flags, time_t mtime);
	void (*send_message)(im_conversation* conv, im_conversation_message* m);
} protocol_plugin_implement;


/**
 * Э�����Ե�������� ���Լ�ע�ᵽȫ�ֱ�����
 * ע����̷����ڳ�������֮ǰ��
 */
#define AUTO_REGIST_PLUGIN_BEFOR_APPRUN(f) \
	static protocol_plugin_register r(f);

typedef void (*PROTOCOL_INIT_FUNC)(void);
class protocol_plugin_register {
public:
	protocol_plugin_register(PROTOCOL_INIT_FUNC f);
};

class protocol_plugin
{
public:
	//protocol_plugin_implement* _imp;

	static void			init(void);
	static void			uninit(void);
	static bool			load_all_plugins(void);
	/**
	 * ע��Э��������Ӧ��Э��
	 * @protocol_name Э������
	 * @imp Э�����ʵ�ֶ���
	 */
	static void			regist_plugin(const char* protocol_name, protocol_plugin_implement* imp);
	static protocol_plugin_implement* find_plugin(const char* protocol_name);
};


#endif