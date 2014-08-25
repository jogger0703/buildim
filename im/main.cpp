#include <stdio.h>
#include "libim/core.h"
#include "mconn.h"
#include "util/error_process.h"
#include "util/config.h"
#include "util/exstring.h"
#include "util/log.h"


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

int main(int argc, char** argv)
{
	g_im_core.init();

	im_connection::set_ui_ops(&conn_ops);
	im_account::set_ui_ops(&account_ops);
	im_conversation::set_ui_ops(&conv_ops);

	im_account acc;
	acc._protocal_name = "eyouim";
	acc._username = "im@eyou.net";
	acc._password = "WmhhbmdodWE1Mjg2MjU=";
	acc.connect_server();

	while (1) {
		Sleep(100);
	}
	g_im_core.quit();
	return 0;
}