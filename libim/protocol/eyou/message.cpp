#include "message.h"
#include "conversation.h"
#include "eyou.h"
#include <time.h>
#include "char_operation.h"
#include "buddy.h"
#include "io.h"

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

void eyou_message::send_message_plain(im_conversation* conv, const char* who, const char* content, im_message_flags flags, time_t mtime)
{
	im_buddy* b = (im_buddy*)conv->_members.front();
	std::string xml = string_format(
		"<message to=\"%s\" type=\"chat\" from=\"%s\" time=\"%I64d\">"\
		"<body color=\"0\" height=\"-13\" width=\"0\" escp=\"0\" "\
		"ort=\"0\" weight=\"400\" charset=\"0\" facename=\"&#x5FAE;&#x8F6F;&#x96C5;&#x9ED1;\" "\
		"italic=\"false\" strikeout=\"false\" underline=\"false\">"\
		"<![CDATA[%s]]></body></message>",
		b->_id.c_str(),
		who,
		mtime,
		content);

	eyou_write_plain(conv->_account->get_connection(), xml.c_str(), xml.length());
}

void eyou_message::send_message(im_conversation* conv, im_conversation_message* m)
{
	send_message_plain(conv, m->_who_sent.c_str(), m->_content.c_str(), m->_flags, m->_time);
}