#include "buddy.h"


/* 好友列表根节点 */
static im_buddy_node*	_roster = NULL;
/* 组织架构根节点，也可能是qq的群 */
//static im_buddy_node*	_structure = NULL;
/* */
static im_buddy_ui_ops* _ops = NULL;

void im_buddy_init()
{
	_roster = new im_buddy_node();
	_roster->_level = 0;
}
void im_buddy_uninit()
{
	if (_roster)
		delete _roster;
	_roster = NULL;
}

void im_buddy_set_ui_ops(im_buddy_ui_ops* ops) {
	_ops = ops;
}
im_buddy_ui_ops* im_buddy_get_ui_ops(void) {
	return _ops;
}

im_buddy_node* im_buddy_get_roster(void) {
	return _roster;
}

//////////////////////////////////////////////////////////////////////////
// im_buddy_node
//////////////////////////////////////////////////////////////////////////

im_buddy_node::im_buddy_node()
{
	_next = _parent = _children = NULL;
	_settings = NULL;
	/* 虚根节点没有类型 */
	_type = LIBIM_BUDDY_NODE_NONE;
	_uidata = NULL;

	_level = 0;
}

void im_buddy_node::add_child(im_buddy_node* node)
{
	if (!_children) {
		_children = node;
	}
	else {
		im_buddy_node* last_child = _children;

		while (last_child && last_child->_next)
			last_child = last_child->_next;
		last_child->_next = node;
	}

	node->_parent = this;
	node->_level = _level+1;
}

void im_buddy_node::clear_children(void)
{
	im_buddy_node* child = _children;
	im_buddy_node* tmp = NULL;
	while (child) {
		child->clear_children();
		tmp = child;
		child = child->get_next();
		delete tmp;
	}
}

im_buddy_node* im_buddy_node::find_child(const char* uid)
{
	im_buddy_node* ret = NULL;
	im_buddy_node* child = _children;
	while (child) {
		if (child->_id == uid) {
			ret = child;
			break;
		}

		ret = child->find_child(uid);
		if (ret == NULL)
			child = child->get_next();
		else
			break;
	}
	return ret;
}

im_buddy_node* im_buddy_node::get_first_child(void) {
	return _children;
}
im_buddy_node* im_buddy_node::get_next(void) {
	return _next;
}
im_buddy_node_type im_buddy_node::get_type(void) {
	return _type;
}
