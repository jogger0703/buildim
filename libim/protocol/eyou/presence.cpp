#include "presence.h"
#include "eyou.h"

void eyou_presence::process(void)
{
	if (_type == "ok") {
		/* ���ڷ������ϵ�״̬�Ѿ��ı� */
		_client->change_status(_client->get_want_status());
	}
}