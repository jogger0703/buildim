#include "presence.h"
#include "eyou.h"

void eyou_presence::process(void)
{
	if (_type == "ok") {
		/* 我在服务器上的状态已经改变 */
		_client->change_status(_client->get_want_status());
	}
}