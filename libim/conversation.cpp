#include "conversation.h"
#include "makeuuid.h"
#include "account.h"
#include "buddy.h"
#include <time.h>


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
 *
 * PS:这个函数有可能被界面调用。也有可能被网络层调用
 * 当用户主动选择好友聊天时，界面层，调用。
 * 当网络消息过来时，网络层调用。
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

/**
 * 发送消息
 * @who，发送者id
 * @content，消息内容
 * @im_message_flags，消息标志
 * @mtime，发送时间，如果为0，则按系统时间发送
 */
void im_conversation::send_message_plain(const char* who, const char* content, im_message_flags flags, time_t mtime)
{
	if (mtime == 0)
		mtime = time(NULL);

	if (_account->_imp->send_message_plain)
		_account->_imp->send_message_plain(this, who, content, flags, mtime);
}

void im_conversation::send_message(im_conversation_message* m)
{
	if (_account->_imp->send_message)
		_account->_imp->send_message(this, m);
}

/**
 * 通过id添加聊天对象。
 * 先在roster中查找，后在组织架构中查找（如果有的话）
 * 成功返回true 失败返回false
 */
bool im_conversation::add_member_by_id(const char* userid)
{
	im_buddy_node* b = im_buddy_get_roster()->find_child(userid);
	if (!b)
		return false;
	add_member(b);
	return true;
}

/**
 * 添加聊天对象。
 * 不管单人还是多人的conversation，此处只管添加。
 */
void im_conversation::add_member(im_buddy_node* buddy)
{
	_members.push_back(buddy);
}

void im_conversation::set_ui_ops(im_conversation_ui_ops* ops) {
	_ops = ops;
}
im_conversation_ui_ops* im_conversation::get_ui_ops() {
	return _ops;
}

