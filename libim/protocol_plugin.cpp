#include "protocol_plugin.h"
#include "value.h"

/**
 * Э�����б�
 * ��Э������Ϊkey
 */
static im_hash_table_string_void plugins_table;

static im_list* init_list;

/**/
protocol_plugin_register::protocol_plugin_register(PROTOCOL_INIT_FUNC f)
{
	if (!init_list)
		init_list = new im_list();

	if (f)
		init_list->push_back((void*)f);
}



void protocol_plugin::init(void)
{
	load_all_plugins();
}
void protocol_plugin::uninit(void)
{

}
bool protocol_plugin::load_all_plugins(void)
{
	while (!init_list->empty()) {
		PROTOCOL_INIT_FUNC init_func = (PROTOCOL_INIT_FUNC)init_list->front();
		init_func();
		init_list->pop_front();
	}
	delete init_list;
	init_list = NULL;
	return true;
}

/**
 * ��Э��ʵ��ע�ᵽȫ���б���
 * Э��������Ψһ�ģ�������ʵ��һ��һ
 */
void protocol_plugin::regist_plugin(const char* protocol_name, protocol_plugin_implement* imp)
{
	plugins_table[protocol_name] = (void*)imp;
}

protocol_plugin_implement* protocol_plugin::find_plugin(const char* protocol_name)
{
	return (protocol_plugin_implement*)plugins_table[protocol_name];
}