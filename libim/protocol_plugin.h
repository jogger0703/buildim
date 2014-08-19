#ifndef ___LIBIM_PROTOCOL_PLUGIN__H__
#define ___LIBIM_PROTOCOL_PLUGIN__H__

#include "value.h"

class im_account;
class im_connection;
class protocol_plugin;
class protocol_plugin_register;

typedef struct
{
	void (*login)(im_account* acc);
	void (*close)(im_connection* conn);
} protocol_plugin_implement;


/**
 * 协议层可以调用这个宏 把自己注册到全局变量中
 * 注册过程发生在程序运行之前。
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
	 * 注册协议插件到相应的协议
	 * @protocol_name 协议名称
	 * @imp 协议具体实现对象
	 */
	static void			regist_plugin(const char* protocol_name, protocol_plugin_implement* imp);
	static protocol_plugin_implement* find_plugin(const char* protocol_name);
};


#endif