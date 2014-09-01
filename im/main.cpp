#include <stdio.h>
#include "libim/core.h"
#include "mconn.h"
#include "console.h"
#include "buddy.h"
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


static void login()
{
	_account.connect_server();
}
static void logout()
{
	if (_account.is_connected())
		_account.disconnect();
}

static void show_roster()
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
			DPRINT(LOG_WARING, "member=%s", b->_uid.c_str());
			b = (im_buddy*)b->get_next();
		}

		g = (im_group*)g->get_next();
	}
}

static void print_help();

struct command_list_st {
	const char* cmd;
	const char* description;
	void (*func)(void);
} cmd_list[] = {
	{"login", "connect and auth to server", login},
	{"roster", "show roster", show_roster},
	{"?", "output help information", print_help},
	{"help", "output help information", print_help},
	{"q", "quit", logout},
};

void print_help()
{
	for (int i=0; i<ARRAY_COUNT(cmd_list); i++) {
		DPRINT(LOG_WARING, "%10s : %s", cmd_list[i].cmd, cmd_list[i].description);
	}
}

static void command_process(const char* cmd)
{
	for (int i=0; i<ARRAY_COUNT(cmd_list); i++) {
		if (strcmp(cmd, cmd_list[i].cmd) == 0) {
			if (cmd_list[i].func != NULL)
				cmd_list[i].func();
			else
				DPRINT(LOG_ERROR, "un implement command!");

			return ;
		}
	}
	DPRINT(LOG_ERROR, "unknown command!");
}

#include <libxml/tree.h>
int main(int argc, char** argv)
{
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