#include "eyou.h"
#include "exstring.h"
#include "value.h"
#include "status.h"
#include "io.h"


//////////////////////////////////////////////////////////////////////////
// eyou_buddy_state
//////////////////////////////////////////////////////////////////////////
static const struct {
	int state;
	const char* name;
} eyou_status[] = {
	//EYOU_BUDDY_STATE_ERROR, "error"
	{LIBIM_STATUS_OFFLINE, "unavailable"},
	{LIBIM_STATUS_AVAILABLE, "available" },
	{LIBIM_STATUS_DND, "busy"},
	{LIBIM_STATUS_AWAY, "away"}
};
const char* eyou_buddy_state_to_string(im_status state)
{
	for (int i=0; i<ARRAY_COUNT(eyou_status); i++) {
		if (eyou_status[i].state == state)
			return eyou_status[i].name;
	}
	return NULL;
}

im_status eyou_buddy_state_to_state(const char* name)
{
	for (int i=0; i<ARRAY_COUNT(eyou_status); i++) {
		if (strcmp(eyou_status[i].name, name) == 0)
			return (im_status)eyou_status[i].state;
	}
	return LIBIM_STATUS_ERROR;
}


void eyou::set_auth_state(eyou_auth_state state)
{
	switch (state) {
	case EYOU_STATE_OFFLINE:
		break;
	case EYOU_STATE_CONNECTING:
		break;
	case EYOU_STATE_CONNECTED:
		{
			// 连接成功，开始登录
			std::string authpack;
			authpack = string_format("<iq method=\"auth\" id=\"101\"><username>%s</username><password>%s</password></iq>",
				_account->_username.c_str(),
				_account->_password.c_str());

			eyou_write_plain(_conn, authpack.c_str(), authpack.length());
			set_auth_state(EYOU_STATE_POST_AUTH);
		}
		break;
	case EYOU_STATE_POST_AUTH:
		break;
	case EYOU_STATE_AUTHED:
		{
			/* 验证通过，将自己的状态提交到服务器，否则好友看到我是离线的 */
			std::string statepack;
			_want_status = LIBIM_STATUS_AVAILABLE;
			statepack = string_format("<presence id=\"104\"><status>%s</status><mood>%s</mood><avatar>%s</avatar><vcard><name>%s</name><gender>%s</gender></vcard></presence>",
				eyou_buddy_state_to_string(_want_status),
				_account->_mood.c_str(),
				_account->_avatar.c_str(),
				_account->_username.c_str(),
				_account->_gender.c_str());
			eyou_write_plain(_conn, statepack.c_str(), statepack.length());

			/* 设置心跳包触发计时器 */
			_conn->set_keep_alive_idle(15);

			set_auth_state(EYOU_STATE_POST_AUTH);
		}
		break;
	default:
		DPRINT(LOG_WARING, "ill state %d", (int)state);
		break;
	}
}

void eyou::change_status(im_status status) {
	if (_account->get_ui_ops()->status_changed)
		_account->get_ui_ops()->status_changed(_account, status);
}
im_status eyou::get_current_status() {
	return _account->get_status();
}
im_status eyou::get_want_status() {
	return _want_status;
}

void eyou::change_status_on_server(im_status status)
{
	char* fmt = "<presence id=\"104\"><status>%s</status></presence>";

	_want_status = status;
	std::string statepack = "";

	switch (_want_status) {
	case LIBIM_STATUS_ERROR:
		DPRINT(LOG_ERROR, "odd, who change my status error?");
		break;
	case LIBIM_STATUS_INVISIBLE:
		/* eyou协议中不存在此状态 */
		break;
	case LIBIM_STATUS_EXTENED_AWAY:
		/* eyou协议中不存在此状态 */
		break;
	case LIBIM_STATUS_OFFLINE:
	case LIBIM_STATUS_AVAILABLE:
	case LIBIM_STATUS_AWAY:
	case LIBIM_STATUS_DND:
		/* 以上四个状态的包状态一样 */
		statepack = string_format(fmt, eyou_buddy_state_to_string(_want_status));
		break;
	default:
		DPRINT(LOG_ERROR, "odd, unknown status %d", status);
		break;
	}

	if (!statepack.empty())
		eyou_write_plain(_conn, statepack.c_str(), statepack.length());

	/**
	 * 当服务器收到离线消息后，可能会主动关闭连接。
	 * 如果服务器关闭套接字，客户端就不需要主动关闭了。
	 * 目前还不确定服务器的做法
	 */
// 	if (status == LIBIM_STATUS_OFFLINE) {
// 		_account->_connection->disconnect();
// 	}
}