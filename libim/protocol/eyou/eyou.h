#ifndef ___LIBIM_EYOU__H__
#define ___LIBIM_EYOU__H__

#include "core.h"
#include "connection.h"
#include "account.h"
#include "status.h"

#pragma comment(lib, "libxml2.lib")

typedef enum {
	/* 离线 */
	EYOU_STATE_OFFLINE = 0,
	/* 正在连接服务器 */
	EYOU_STATE_CONNECTING,
	/* 连接服务器成功 */
	EYOU_STATE_CONNECTED,
	/* 发送了验证包 */
	EYOU_STATE_POST_AUTH,
	/**
	 * 验证通过，
	 * 用户状态是否有效是以此为前提的
	 * 如果验证没有通过，用户状态无效
	 */
	EYOU_STATE_AUTHED,
} eyou_auth_state;

const char* eyou_buddy_state_to_string(im_status state);
im_status eyou_buddy_state_to_state(const char* name);

class eyou
{
	/* 连接状态 */
	eyou_auth_state		_auth_state;
	/**
	 * 期望的用户状态，比如：当界面切换忙碌时，期望状态会改变为忙碌
	 * 直到服务器返回状态设置成功，目前状态才等于期望状态
	 *
	 * 当前状态在im_account中
	 */
	im_status			_want_status;
public:
	im_connection*		_conn;
	im_account*			_account;

	/**
	 * 设置用户登录状态，验证登录期间会使用
	 */
	void				set_auth_state(eyou_auth_state state);
	bool				is_authed(void) {return (_auth_state == EYOU_STATE_AUTHED);}

	/**
	 * 通知服务器要更改我的在线状态
	 * eyou服务器在收到这个状态请求之后，会返回一个presence响应包，来通知客户端修改成功
	 * 状态包括：im_status中的元素
	 */
	void				change_status_on_server(im_status status);
	/* 设置本地的状态 */
	void				change_status(im_status status);
	im_status			get_current_status();
	im_status			get_want_status();

#ifdef STREAM_PARSE 
	/* libxml 解析库上下文 */
	xmlParserCtxtPtr	_context;
	/* 当前解析的节点 */
	xmlNodePtr			_current;
#endif
};



#endif