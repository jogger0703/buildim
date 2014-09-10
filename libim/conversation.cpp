#include "conversation.h"
#include "makeuuid.h"
#include "account.h"
#include "buddy.h"
#include <time.h>


static im_conversation_ui_ops* _ops;

/**
 * ȫ�ֵĻỰ�б� 
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
 * �½�һ���Ự��
 * �½��ɹ�֮�󣬻���ӵ�ȫ�ֻ����С�
 * ����������Ѿ����ڣ������½���ֱ�ӷ��ػ���Ķ���
 * @username im_account���û���
 * @conv_name �Ự���֣�����Ψһ��
 * @type �Ự����
 * �ɹ����ض���ָ�룬ʧ�ܷ���NULL
 *
 * PS:��������п��ܱ�������á�Ҳ�п��ܱ���������
 * ���û�����ѡ���������ʱ������㣬���á�
 * ��������Ϣ����ʱ���������á�
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
 * ���һỰ
 * �ɹ����ض���ָ�룬ʧ�ܷ���NULL
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
 * ������Ϣ
 * @who��������id
 * @content����Ϣ����
 * @im_message_flags����Ϣ��־
 * @mtime������ʱ�䣬���Ϊ0����ϵͳʱ�䷢��
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
 * ͨ��id����������
 * ����roster�в��ң�������֯�ܹ��в��ң�����еĻ���
 * �ɹ�����true ʧ�ܷ���false
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
 * ����������
 * ���ܵ��˻��Ƕ��˵�conversation���˴�ֻ����ӡ�
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

