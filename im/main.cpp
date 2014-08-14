#include <stdio.h>
#include "libim/core.h"
#include "libim/connection.h"
#include "util/error_process.h"

static void connect_progress(im_connection* conn, const char* text, size_t current_step, size_t step_count) {
	
}
static void connected(im_connection* conn) {
	
}
static void disconnected(im_connection* conn) {
	
}
static void notice(im_connection* conn, const char* text) {
	
}
static void network_connected(im_connection* conn) {
	printf("connected %s:%s\n", conn->_host.c_str(), conn->_serv.c_str());
}
static void network_disconnected(im_connection* conn) {
	
}
static void report_disconnect(im_connection *gc, const char *text) {
	
}
static void network_error(im_connection* conn, int err) {
	int n = err;
	printf("connect error:%s", errno2msg(err).c_str());
}

std::wstring

static im_connection_ui_ops ops =
{
	NULL,
	NULL,
	NULL,
	NULL,
	network_connected,
	network_disconnected,
	NULL,
	network_error
};

im_connection conn;

int main(int argc, char** argv)
{
	g_im_core.init();

	conn.set_ui_ops(&ops);
	conn.connect("172.16.100.223", "7732");
	
	conn.disconnect();
	return 0;
}