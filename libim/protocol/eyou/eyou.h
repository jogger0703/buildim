#ifndef ___LIBIM_EYOU__H__
#define ___LIBIM_EYOU__H__

#include "core.h"
#include "connection.h"
#include "account.h"
#include "status.h"

#pragma comment(lib, "libxml2.lib")

typedef enum {
	/* ���� */
	EYOU_STATE_OFFLINE = 0,
	/* �������ӷ����� */
	EYOU_STATE_CONNECTING,
	/* ���ӷ������ɹ� */
	EYOU_STATE_CONNECTED,
	/* ��������֤�� */
	EYOU_STATE_POST_AUTH,
	/**
	 * ��֤ͨ����
	 * �û�״̬�Ƿ���Ч���Դ�Ϊǰ���
	 * �����֤û��ͨ�����û�״̬��Ч
	 */
	EYOU_STATE_AUTHED,
} eyou_auth_state;

const char* eyou_buddy_state_to_string(im_status state);
im_status eyou_buddy_state_to_state(const char* name);

class eyou
{
	/* ����״̬ */
	eyou_auth_state		_auth_state;
	/**
	 * �������û�״̬�����磺�������л�æµʱ������״̬��ı�Ϊæµ
	 * ֱ������������״̬���óɹ���Ŀǰ״̬�ŵ�������״̬
	 *
	 * ��ǰ״̬��im_account��
	 */
	im_status			_want_status;
public:
	im_connection*		_conn;
	im_account*			_account;

	/**
	 * �����û���¼״̬����֤��¼�ڼ��ʹ��
	 */
	void				set_auth_state(eyou_auth_state state);
	bool				is_authed(void) {return (_auth_state == EYOU_STATE_AUTHED);}

	/**
	 * ֪ͨ������Ҫ�����ҵ�����״̬
	 * eyou���������յ����״̬����֮�󣬻᷵��һ��presence��Ӧ������֪ͨ�ͻ����޸ĳɹ�
	 * ״̬������im_status�е�Ԫ��
	 */
	void				change_status_on_server(im_status status);
	/* ���ñ��ص�״̬ */
	void				change_status(im_status status);
	im_status			get_current_status();
	im_status			get_want_status();

#ifdef STREAM_PARSE 
	/* libxml ������������ */
	xmlParserCtxtPtr	_context;
	/* ��ǰ�����Ľڵ� */
	xmlNodePtr			_current;
#endif
};



#endif