#ifndef ___LIBIM_EYOU__H__
#define ___LIBIM_EYOU__H__

#include "core.h"

typedef enum {
	EYOU_STATE_OFFLINE,
	EYOU_STATE_CONNECTING,
	EYOU_STATE_POST_AUTH,
	EYOU_STATE_CONNECTED
} eyou_connect_state;

class eyou
{
public:
	im_connection*		_conn;
	im_account*			_account;
};


#endif