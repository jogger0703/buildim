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
	 * 新加节点，中间层添加节点之后。会以此回调通知界面
	 * @node是已经创建好的节点。里边的信息都是可以使用的
	 */
	void (*new_node)(im_buddy_node* node);
	void (*remove_node)(im_buddy_node* node);
} im_buddy_ui_ops;

/**
 * 联系人，组织架构节点的基础类。
 * 这个类有树形结构的特点
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
 * 组织节点
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
 * 组节点
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
 * 联系人。
 * 用于好友列表中。
 * 一般认为，联系人比组织架构的中的子节点字段要多一些。
 * 但是为了自由和扩展，不能继承自组织架构的im_buddy类
 * 好友节点与组织节点字段不见的是完全的包含关系
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