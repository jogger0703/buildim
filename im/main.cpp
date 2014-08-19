#include <stdio.h>
#include "libim/core.h"
#include "mconn.h"
#include "util/error_process.h"
#include "util/config.h"

static void network_connected(im_connection* conn) {
	printf("connected %s:%s\n", conn->_host.c_str(), conn->_serv.c_str());
}
static void network_disconnected(im_connection* conn) {

}
static void network_error(im_connection* conn, int err) {
	int n = err;
	printf("connect error:%s", errno2msg(err).c_str());
}

static im_connection_ui_ops ops =
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


int main(int argc, char** argv)
{
	g_im_core.init();
	im_connection::set_ui_ops(&ops);

	im_account acc;
	acc._protocal_name = "eyouim";
	acc._username = "im@eyou.net";
	acc._password = "Zhanghua528625";
	acc.connect_server();

	while (1) {
		Sleep(100);
	}
	g_im_core.quit();
	return 0;
}