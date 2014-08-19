#include "workq.h"

// 
WorkQ::WorkQ(void)
{
	valid = 0;
	InitializeCriticalSection(&cs);
}
WorkQ::~WorkQ(void)
{
	DeleteCriticalSection(&cs);
}
//////////////////////////////////////////////////////////////////////////
/* 
 * ��ʼ���̳߳�
 * max:�̳߳ص��������
 * worker_count:��󲢷���
 * timeout:��ʱ����
 * func_do:������
 * �ɹ�����0��ʧ�ܷ��ش�����
 */
int 
WorkQ::init(int max, int paiallel, int timeout, FUNC_CALLBACK func_do)
{
	if (!func_do || max <= 0 || paiallel <= 0)
		return WQ_BADPRA;

	this->max_work = max;
	this->max_worker_count = paiallel;
	this->timeout = timeout;
	this->func = func_do;
	this->cur_work = this->cur_worker_count = 0;
	this->first = this->last = NULL;
	this->quit = 0;

	this->valid = 1;
	return WQ_OK;
}

/* 
 * �����̳߳�
 * �ɹ�����0��ʧ�ܷ��ش�����
 */
int 
WorkQ::destroy(void)
{
	if (!valid)
		return WQ_INVAL;

	lock();
	quit = 1;
	valid = 0;
	unlock();

	// �ȴ������߳��˳�
	// ����ȴ�����2�룬���ٵȴ�
	int waited = 2000;
	while (cur_worker_count > 0
		  && waited > 0) {
		Sleep(50);
		waited -= 50;
	}

	return WQ_OK;
}
/* 
 * ���̳߳����������
 * data������
 * �ɹ�����0��ʧ�ܷ��ش�����
 */
int 
WorkQ::add_work(void* data)
{
	workq_ele_t* new_ele = NULL;

	if (!valid)
		return WQ_INVAL;
	if (cur_work >= max_work)
		return WQ_FULL;
	if (quit)
		return WQ_QUIT;

	new_ele = new workq_ele_t();
	if (!new_ele)
		return WQ_NOMEM;
	new_ele->data = data;
	new_ele->next = NULL;

	/* ��Ϊ��Ҫ���ĳ�Ա���������� */
	lock();
	if (!first)
		first = new_ele;
	else
		last->next = new_ele;
	last = new_ele;
	cur_work++;
	/* ���� */
	unlock();

	// ����п����̣߳����贴�����߳�
	if (idle > 0)
		return WQ_OK;

	if (cur_worker_count < max_worker_count) {
		HANDLE fd = ::CreateThread(0, 0, thread_do_it, this, 0, NULL);
		if (!fd) {
			return WQ_ERROR;
		}
		cur_worker_count++;
	}

	return WQ_OK;
}

/* 
 * �����̲߳�������
 */
int
WorkQ::modify_paiallel(int max)
{
	if (max <= 0)
		return WQ_BADPRA;

	lock();
	max_worker_count = max;
	unlock();
	return WQ_OK;
}
/* 
 * �̺߳���
 */
DWORD
WorkQ::thread_do_it(void* arg)
{
	WorkQ* wq = (WorkQ*)arg;
	workq_ele_t* ele = NULL;

	while (!wq->quit) {
		// �깤��ʶ����ʾ�������������
		int all_done = 0;
		while (!wq->first && !wq->quit) {
			if (!all_done)
				wq->idle++;
			// ��ֹ�߳̿�ת
			Sleep(50);
			all_done = 1;
			// ���������̫�࣬�Ծ��˳�
			if (wq->cur_worker_count > wq->max_worker_count)
				break;
		}
		// �л���ˣ��Ծ���ȥ������
		wq->idle--; 
		// ���������̫�࣬�Ծ��˳�
		if (wq->cur_worker_count > wq->max_worker_count)
			break;

		/* �õ������Ժ󣬽����񵯳����׺�/���β */
		wq->lock();
		ele = wq->first;
		if (!ele)
			continue;
		wq->first = ele->next;
		if (wq->last == ele)
			wq->last = NULL;
		wq->cur_work--;
		wq->unlock();

		// ����
		wq->func(ele->data);
		delete ele;
		ele = NULL;
	}

	// �뿪���˶���
	wq->cur_worker_count--;
	return 0;
}

//////////////////////////////////////////////////////////////////////////
void WorkQ::lock() {
	EnterCriticalSection(&cs);
}
void WorkQ::unlock() {
	LeaveCriticalSection(&cs);
}
