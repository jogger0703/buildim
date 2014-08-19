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
 * 初始化线程池
 * max:线程池的最大容量
 * worker_count:最大并发数
 * timeout:超时粒度
 * func_do:处理函数
 * 成功返回0，失败返回错误码
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
 * 销毁线程池
 * 成功返回0，失败返回错误码
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

	// 等待所有线程退出
	// 如果等待超过2秒，不再等待
	int waited = 2000;
	while (cur_worker_count > 0
		  && waited > 0) {
		Sleep(50);
		waited -= 50;
	}

	return WQ_OK;
}
/* 
 * 向线程池中添加任务
 * data：数据
 * 成功返回0，失败返回错误码
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

	/* 因为需要更改成员变量，加锁 */
	lock();
	if (!first)
		first = new_ele;
	else
		last->next = new_ele;
	last = new_ele;
	cur_work++;
	/* 解锁 */
	unlock();

	// 如果有空闲线程，无需创建新线程
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
 * 调整线程并行数量
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
 * 线程函数
 */
DWORD
WorkQ::thread_do_it(void* arg)
{
	WorkQ* wq = (WorkQ*)arg;
	workq_ele_t* ele = NULL;

	while (!wq->quit) {
		// 完工标识，表示所有任务都完成了
		int all_done = 0;
		while (!wq->first && !wq->quit) {
			if (!all_done)
				wq->idle++;
			// 防止线程空转
			Sleep(50);
			all_done = 1;
			// 如果工人数太多，自觉退出
			if (wq->cur_worker_count > wq->max_worker_count)
				break;
		}
		// 有活干了，自觉减去空闲数
		wq->idle--; 
		// 如果工人数太多，自觉退出
		if (wq->cur_worker_count > wq->max_worker_count)
			break;

		/* 拿到任务以后，将任务弹出队首和/或队尾 */
		wq->lock();
		ele = wq->first;
		if (!ele)
			continue;
		wq->first = ele->next;
		if (wq->last == ele)
			wq->last = NULL;
		wq->cur_work--;
		wq->unlock();

		// 工作
		wq->func(ele->data);
		delete ele;
		ele = NULL;
	}

	// 离开工人队列
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
