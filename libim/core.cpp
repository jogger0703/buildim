#include "core.h"
#include "signal.h"
#include "connection.h"
#include "protocol_plugin.h"
#include "../util/network.h"

im_core g_im_core;

bool im_core::init() 
{
	winsock_init();
	im_connection::init();
	protocol_plugin::init();

	return true;
}

void im_core::quit()
{
	im_connection::uninit();
}

im_core* im_core::get_core()
{
	return &g_im_core;
}
im_core_ui_ops* im_core::get_ui_ops()
{
	return ops;
}
void im_core::set_ui_ops(im_core_ui_ops* ops)
{
	ops = ops;
}