#ifndef ___LIBIM_BUDDY__H__
#define ___LIBIM_BUDDY__H__

#include "config.h"
#include "status.h"

typedef enum {
	LIBIM_BUDDY_NODE_GROUP,
	LIBIM_BUDDY_NODE_BUDDY
} im_buddy_node_type;

/**
 * ��ϵ�ˣ���֯�ܹ��ڵ�Ļ����ࡣ
 * ����������νṹ���ص�
 */
class im_buddy_node
{
	im_buddy_node_type	_type;

	im_buddy_node*		_prev;
	im_buddy_node*		_next;
	im_buddy_node*		_children;
	im_buddy_node*		_parent;

	hash_config*		_settings;
public:
	virtual ~im_buddy_node() {}
	void*				_uidata;
};

/**
 * ��֯�ڵ�
 */
class im_buddy : public im_buddy_node
{
public:
	virtual ~im_buddy() {}

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
	virtual ~im_group() {}
	
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
	virtual ~im_contact() {}

	std::string			_name;
	std::string			_alias;
	im_status			_status;
};



#endif