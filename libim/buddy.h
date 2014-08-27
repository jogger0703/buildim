#ifndef ___LIBIM_BUDDY__H__
#define ___LIBIM_BUDDY__H__

#include "config.h"
#include "status.h"

typedef enum {
	LIBIM_BUDDY_NODE_GROUP,
	LIBIM_BUDDY_NODE_BUDDY
} im_buddy_node_type;

/**
 * 联系人，组织架构节点的基础类。
 * 这个类有树形结构的特点
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
 * 组织节点
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
 * 组节点
 */
class im_group : public im_buddy_node
{
public:
	virtual ~im_group() {}
	
};

/**
 * 联系人。
 * 用于好友列表中。
 * 一般认为，联系人比组织架构的中的子节点字段要多一些。
 * 但是为了自由和扩展，不能继承自组织架构的im_buddy类
 * 好友节点与组织节点字段不见的是完全的包含关系
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