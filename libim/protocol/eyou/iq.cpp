#include "iq.h"
#include "eyou.h"
#include "value.h"
#include "roster.h"
#include "buddy.h"

void eyou_iq::process(void)
{
	if (_method == "auth") {
		if (_type == "ok") {
			_client->set_auth_state(EYOU_STATE_AUTHED);
		}
	}
	//<iq id="2" type="ok" to="im@eyou.net" method="roster">
	else if (_method == "roster") {
		if (_type == "ok") {
			parse_roster_from_xml(im_buddy_get_roster(), _str.c_str());
		}
	}
}