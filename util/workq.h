/*
workq.h
�̳߳���

create date:2011.12.14
author:zhaoxueqian

*/
#ifndef _WORK_Q_H_
#define _WORK_Q_H_

#include <Windows.h>


#define WQ_OK         0  // �ɹ�
#define WQ_INVAL      -1 // δ��ʼ��
#define WQ_BADPRA     -2 // ��������
#define WQ_FULL       -3 // ��������
#define WQ_NOMEM      -4 // �ڴ治��
#define WQ_ERROR      -5 // δ֪����
#define WQ_QUIT       -6 // �̳߳��˳�

// workq element
typedef struct workq_ele_st {
	struct workq_ele_st* next;
	void* data;
} workq_ele_t;

// callback function
typedef int (*FUNC_CALLBACK)(void* arg);

// class workq
class WorkQ
{
public:
	int init(int max, int paiallel, int timeout, FUNC_CALLBACK func_do);
	int destroy(void);
	int add_work(void* data);
	int modify_paiallel(int paiallel);
public:
	WorkQ(void);
	~WorkQ(void);
private:
	inline void lock();
	inline void unlock();
	static DWORD WINAPI thread_do_it(void* arg);
private:
	CRITICAL_SECTION cs;     // ��	
	FUNC_CALLBACK func;      // �̺߳���
	int max_work;            // ���������
	int max_worker_count;     // ��󲢷���
	int cur_work;            // ��ǰ������
	volatile int cur_worker_count;// ��ǰ�߳���
	volatile int idle;       // �����߳���
	int timeout;             // ��ʱ����
	// ��β����
	workq_ele_t* first;
	workq_ele_t* last;

	int valid;               // ��ʼ�����
	int quit;                // �˳����
};


#endif // ~_WORK_Q_H_