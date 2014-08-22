#include "conversation.h"

static im_conversation_ui_ops* _ops;


void im_conversation::init()
{}
void im_conversation::uninit()
{}

void im_conversation::set_ui_ops(im_conversation_ui_ops* ops) {
	_ops = ops;
}
im_conversation_ui_ops* im_conversation::get_ui_ops() {
	return _ops;
}
