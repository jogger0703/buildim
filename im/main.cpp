#include <stdio.h>
#include "libim/core.h"
#include "mconn.h"
#include "console.h"
#include "buddy.h"
#include <Windows.h>
#include <time.h>
#include "util/error_process.h"
#include "util/config.h"
#include "util/exstring.h"
#include "util/log.h"


win_console console;


//////////////////////////////////////////////////////////////////////////
// connection ui
//////////////////////////////////////////////////////////////////////////

static void network_connected(im_connection* conn) {
	// TODO
}
static void network_disconnected(im_connection* conn) {
	// TODO
}
static void network_error(im_connection* conn, int err) {
	// TODO
}

static im_connection_ui_ops conn_ops =
{
	NULL,
	NULL,
	NULL,
	NULL,
	network_connected,
	network_disconnected,
	NULL,
	network_error,
};

//////////////////////////////////////////////////////////////////////////
// account ui
//////////////////////////////////////////////////////////////////////////
void status_changed(im_account* account, im_status status)
{
	DPRINT(LOG_INFO, "%s change status -> %d", account->_username.c_str(), status);
}

static im_account_ui_ops account_ops =
{
	status_changed
};

//////////////////////////////////////////////////////////////////////////
// conversation ui
//////////////////////////////////////////////////////////////////////////

void create_conversation(im_conversation* conv) {
	
}
void destroy_conversation(im_conversation* conv) {
	
}
void receive_message(im_conversation* conv, const char* who,
	const char* content, im_message_flags flags, time_t mtime) {
	DPRINT(LOG_WARING, "%s->%s:%s", who, conv->_account->_username.c_str(), content);
}

static im_conversation_ui_ops conv_ops = {
	create_conversation,
	destroy_conversation,
	receive_message
};

//////////////////////////////////////////////////////////////////////////
// main
//////////////////////////////////////////////////////////////////////////
im_account _account;


static void login(char* arg[])
{
	_account.connect_server();
}
static void logout(char* arg[])
{
	if (_account.is_connected())
		_account.disconnect();
}

static void show_roster(char* arg[])
{
	im_buddy_node* roster = im_buddy_get_roster();
	if (!roster) {
		DPRINT(LOG_ERROR, "get roster failed!");
		return;
	}
	im_group* g = (im_group*)roster->get_first_child();
	while (g) {
		DPRINT(LOG_WARING, "group=%s", g->_name.c_str());
		im_buddy* b = (im_buddy*)g->get_first_child();
		while (b) {
			DPRINT(LOG_WARING, "member=%s", b->_id.c_str());
			b = (im_buddy*)b->get_next();
		}

		g = (im_group*)g->get_next();
	}
}

static void tell(char* arg[]/*const char* buddy, const char* content*/)
{
	im_conversation* conv = im_conversation::make_conversation(&_account, arg[1], LIBIM_CONV_TYPE_SINGLE);
	conv->add_member_by_id(arg[1]);
	conv->send_chat(_account.get_username().c_str(), arg[2], LIBIM_MESSAGE_SEND, 0);
}

static void print_help(char* arg[]);

struct command_list_st {
	const char* cmd;
	const char* description;
	void (*func)(char* arg[]);
} cmd_list[] = {
	{"login", "connect and auth to server", login},
	{"roster", "show roster", show_roster},
	{"tell", "tell somebuddy something", tell},
	{"?", "output help information", print_help},
	{"help", "output help information", print_help},
	{"q", "quit", logout},
};

void print_help(char* arg[])
{
	for (int i=0; i<ARRAY_COUNT(cmd_list); i++) {
		DPRINT(LOG_WARING, "%10s : %s", cmd_list[i].cmd, cmd_list[i].description);
	}
}

static void command_process(const char* line)
{
	/**
	 * "tell somebody something"
	 * arg[0] = tell;
	 * arg[1] = somebody;
	 * arg[2] = something;
	 * ...
	 */
	char* arg[5] = {0,0,0,0,0};

	char* src = _strdup(line);
	char* saveptr;
	char* tok = strtok_s(src, " ", &saveptr);
	int i = 0;
	while (tok != NULL) {
		arg[i++] = _strdup(tok);
		tok = strtok_s(NULL, " ", &saveptr);

		if (i >= 5) {
			DPRINT(LOG_ERROR, "TOO many args");
			return;
		}
	}


	for (int i=0; i<ARRAY_COUNT(cmd_list); i++) {
		if (strcmp(arg[0], cmd_list[i].cmd) == 0) {
			if (cmd_list[i].func != NULL) {
				cmd_list[i].func(arg);
			}
			else {
				DPRINT(LOG_ERROR, "un implement command!");
			}
			break;
		}
	}

	if (i >= ARRAY_COUNT(cmd_list))
		DPRINT(LOG_ERROR, "unknown command!");

	for (int i=0; i<5; i++)
		if (arg[i]) delete arg[i];
	delete []src;
}

#include <libxml/tree.h>
int main(int argc, char** argv)
{
	std::string xml = string_format(
		"<message to=\"%s\" type=\"chat\" from=\"%s\" time=\"%d\">"\
		"<body color=\"0\" height=\"-13\" width=\"0\" escp=\"0\" "\
		"ort=\"0\" weight=\"400\" charset=\"0\" facename=\"&#x5FAE;&#x8F6F;&#x96C5;&#x9ED1;\" "\
		"italic=\"false\" strikeout=\"false\" underline=\"false\">"\
		"<![CDATA[%s]]></body></message>",
		"shenjiacheng@eyou.net",
		"im@eyou.net",
		0,
		"hello");

// 	xmlDocPtr doc = NULL;
// 	xmlNodePtr root = NULL;
// 
// 	char buf[10000] = {0};
// 	FILE* f = fopen("b.xml", "r");
// 	int len = fread(buf, 1, 10000, f);
// 
// 	if ((doc = xmlParseMemory(buf, 10000)) == NULL)
// 		return NULL;

	g_im_core.init();


	im_connection::set_ui_ops(&conn_ops);
	im_account::set_ui_ops(&account_ops);
	im_conversation::set_ui_ops(&conv_ops);

	_account._protocal_name = "eyouim";
	_account._username = "im@eyou.net";
	_account._password = "WmhhbmdodWE1Mjg2MjU=";

	console.set_process_cb(command_process);
	console.run_loop();

	g_im_core.quit();
	return 0;
}