#ifndef ___LIBIM_BUDDY__H__
#define ___LIBIM_BUDDY__H__

#include "config.h"
#include "status.h"

typedef enum {
	LIBIM_BUDDY_NODE_NONE = 0,
	LIBIM_BUDDY_NODE_GROUP = 1,
	LIBIM_BUDDY_NODE_BUDDY,
	LIBIM_BUDDY_NODE_CONTACT
} im_buddy_node_type;


class im_buddy_node;
class im_buddy;
class im_group;
class im_contact;


typedef struct
{
	/** 
	 * �¼ӽڵ㣬�м����ӽڵ�֮�󡣻��Դ˻ص�֪ͨ����
	 * @node���Ѿ������õĽڵ㡣��ߵ���Ϣ���ǿ���ʹ�õ�
	 */
	void (*new_node)(im_buddy_node* node);
	void (*remove_node)(im_buddy_node* node);
} im_buddy_ui_ops;

/**
 * ��ϵ�ˣ���֯�ܹ��ڵ�Ļ����ࡣ
 * ����������νṹ���ص�
 */
class im_buddy_node
{
	im_buddy_node*		_next;
	im_buddy_node*		_children;
	im_buddy_node*		_parent;

	hash_config*		_settings;
public:
	im_buddy_node_type	_type;

	im_buddy_node();
	virtual ~im_buddy_node() {}

	void*				_uidata;

	void				add_child(im_buddy_node* node);
	im_buddy_node*		get_first_child(void);
	im_buddy_node*		get_next(void);
	im_buddy_node_type	get_type(void);

	void				clear_children(void);
};

/**
 * ��֯�ڵ�
 */
class im_buddy : public im_buddy_node
{
public:
	im_buddy() {_type = LIBIM_BUDDY_NODE_BUDDY;}
	virtual ~im_buddy() {}

	std::string			_uid; // user id
	std::string			_name;
	std::string			_alias;
	im_status			_status;
};

/**
 * ��ڵ�
 */
class im_group : public im_buddy_node
{
public:
	im_group() {_type = LIBIM_BUDDY_NODE_GROUP;}
	virtual ~im_group() {}

	std::string		_name;
	std::string		_goup_type; // eyou group type
	std::string		_pos;
};

/**
 * ��ϵ�ˡ�
 * ���ں����б��С�
 * һ����Ϊ����ϵ�˱���֯�ܹ����е��ӽڵ��ֶ�Ҫ��һЩ��
 * ����Ϊ�����ɺ���չ�����ܼ̳�����֯�ܹ���im_buddy��
 * ���ѽڵ�����֯�ڵ��ֶβ���������ȫ�İ�����ϵ
 */
class im_contact : public im_buddy_node
{
public:
	im_contact() {_type = LIBIM_BUDDY_NODE_CONTACT;}
	virtual ~im_contact() {}

	std::string			_uid; // user id
	std::string			_name;
	std::string			_alias;
	im_status			_status;
};


void im_buddy_init();
void im_buddy_uninit();

void im_buddy_set_ui_ops(im_buddy_ui_ops* ops);
im_buddy_ui_ops* im_buddy_get_ui_ops(void);

im_buddy_node* im_buddy_get_roster(void);


#endif