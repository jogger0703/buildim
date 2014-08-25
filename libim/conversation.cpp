#include "conversation.h"
#include "makeuuid.h"


static im_conversation_ui_ops* _ops;

/**
 * 全局的会话列表 
 */
static im_hash_table_string_void _converstations;
static std::string make_key(const char* a, const char* b, im_conversation_type type)
{
	return string_format("%s:%s:%d", a, b, type);
}

im_conversation::im_conversation()
{
};

void im_conversation::init()
{}
void im_conversation::uninit()
{}


/**
 * 新建一个会话，
 * 新建成功之后，会添加到全局缓存中。
 * 如果缓存中已经存在，不会新建，直接返回缓存的对象
 * @username im_account的用户名
 * @conv_name 会话名字，具有唯一性
 * @type 会话类型
 * 成功返回对象指针，失败返回NULL
 */
im_conversation* im_conversation::make_conversation(im_account* acc, const char* conv_name, im_conversation_type type)
{
	im_conversation* conv = find_conversation(acc, conv_name, type);
	if (conv)
		return conv;

	conv = new im_conversation();
	conv->_name = conv_name;
	conv->_type = type;
	conv->_account = acc;
	_converstations[make_key(acc->_username.c_str(), conv_name, type)] = conv;

	if (_ops && _ops->create_conversation)
		_ops->create_conversation(conv);

	return conv;
}

/**
 * 查找会话
 * 成功返回对象指针，失败返回NULL
 */
im_conversation* im_conversation::find_conversation(im_account* acc, const char* conv_name, im_conversation_type type)
{
	return (im_conversation*)_converstations[make_key(acc->_username.c_str(), conv_name, type)];
}

void im_conversation::remove_conversation(im_conversation* conv)
{
	if (_ops && _ops->destroy_conversation)
		_ops->destroy_conversation(conv);

	std::string k = make_key(conv->_account->_username.c_str(), conv->_name.c_str(), conv->_type);
	 _converstations.erase(k);
}


// void im_conversation::add_cache(im_conversation* conv)
// {
// 	_conversations.push_back((void*)conv);
// }
// void im_conversation::remove_cache(im_conversation* conv)
// {
// 	
// }
// im_conversation* im_conversation::find_cache(im_account* account, const char* name)
// {
// 	for (auto it=_conversations.begin(); it!=_conversations.end(); it++) {
// 		im_conversation* c = (im_conversation*)&it;
// 		if (c->_account == account && c->_name == name)
// 			return c;
// 	}
// 
// 	return NULL;
// }

void im_conversation::set_ui_ops(im_conversation_ui_ops* ops) {
	_ops = ops;
}
im_conversation_ui_ops* im_conversation::get_ui_ops() {
	return _ops;
}

