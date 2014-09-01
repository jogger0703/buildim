#include "message.h"
#include "conversation.h"
#include "eyou.h"
#include <time.h>
#include "char_operation.h"

void eyou_message::process(void)
{
	if (_type == "event") {
		
	}
	else if (_type == "chat") {
		if (_from.empty()) {
			DPRINT(LOG_ERROR, "chat message unknown source!(%s)", _str.c_str());
		}
		
		im_conversation* conv = 
			im_conversation::make_conversation(_client->_account, _from.c_str(), LIBIM_CONV_TYPE_SINGLE);

		xmlNodePtr body = xmlnode_get_child_by_name(_root, "body");
		std::string content = xmlnode_get_value(body);
// 		content = utf82ansi(content.c_str(), content.length());
		
		time_t time = atoi(xmlnode_get_prop(_root, "time").c_str());

		conv->get_ui_ops()->receive_message(conv, _from.c_str(), content.c_str(), LIBIM_MESSAGE_RECV, time);
	}
}