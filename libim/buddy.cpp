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
}

void im_buddy_node::add_child(im_buddy_node* node)
{
	if (!_children) {
		_children = node;
		return;
	}

	im_buddy_node* last_child = _children;

	while (last_child && last_child->_next)
		last_child = last_child->_next;

	node->_parent = this;

	last_child->_next = node;
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

im_buddy_node* im_buddy_node::get_first_child(void) {
	return _children;
}
im_buddy_node* im_buddy_node::get_next(void) {
	return _next;
}
im_buddy_node_type im_buddy_node::get_type(void) {
	return _type;
}
