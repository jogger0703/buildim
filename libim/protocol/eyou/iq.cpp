#include "iq.h"
#include "eyou.h"
#include "value.h"

void eyou_iq::process(void)
{
	if (_method == "auth") {
		if (_type == "ok") {
			_client->set_auth_state(EYOU_STATE_AUTHED);
		}
	}
}