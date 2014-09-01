#include "core.h"
#include "signal.h"
#include "connection.h"
#include "protocol_plugin.h"
#include "buddy.h"
#include "../util/network.h"

im_core g_im_core;

bool im_core::init() 
{
	winsock_init();
	im_connection::init();
	protocol_plugin::init();
	im_buddy_init();
	
	/* NULL代表将调试信息打印到标准输出
	 * 标准输出是给用户看的，不需要打印行号等详细信息
	 */
	DPRINT_INIT(NULL, LOG_INFO, true, false);
	//DPRINT_INIT("log.txt", LOG_INFO, true, true);

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