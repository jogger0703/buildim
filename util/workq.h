/*
workq.h
线程池类

create date:2011.12.14
author:zhaoxueqian

*/
#ifndef _WORK_Q_H_
#define _WORK_Q_H_

#include <Windows.h>


#define WQ_OK         0  // 成功
#define WQ_INVAL      -1 // 未初始化
#define WQ_BADPRA     -2 // 参数错误
#define WQ_FULL       -3 // 队列已满
#define WQ_NOMEM      -4 // 内存不足
#define WQ_ERROR      -5 // 未知错误
#define WQ_QUIT       -6 // 线程池退出

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
	CRITICAL_SECTION cs;     // 锁	
	FUNC_CALLBACK func;      // 线程函数
	int max_work;            // 最大任务数
	int max_worker_count;     // 最大并发数
	int cur_work;            // 当前任务数
	volatile int cur_worker_count;// 当前线程数
	volatile int idle;       // 空闲线程数
	int timeout;             // 超时粒度
	// 首尾任务
	workq_ele_t* first;
	workq_ele_t* last;

	int valid;               // 初始化标记
	int quit;                // 退出标记
};


#endif // ~_WORK_Q_H_