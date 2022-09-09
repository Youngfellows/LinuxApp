#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include "./Global.h"
#include "./Task.h"

/**
 * @brief 线程池管理类
 *
 */
class ThreadPool
{
private:
    static std::shared_ptr<vector<Task *>> mVecTaskLit; //任务列表
    static bool shutdown;                               //线程退出标志
    static pthread_mutex_t mThreadMutex;                //线程同步互斥锁
    static pthread_cond_t mThreadCond;                  //线程同步条件变量
    pthread_t *mThreadId;                               //线程ID指针变量
    int mThreadNum;                                     //线程池中启动的线程数

public:
    ThreadPool(int threadNum); //构造函数
    ~ThreadPool();             //析构函数
    int addTask(Task *task);   //把任务添加到任务队列中
    int stopAll();             //使线程池中的所有线程都退出
    int getTaskSize();         //获取当前任务队列中的任务数

protected:
    static void *threadFunc(void *threadData); //新线程的线程回调函数
    static int moveToIdle(pthread_t tid);      //线程执行结束后,把自己放入空闲线程中去
    static int moveToBusy(pthread_t tid);      //移入到忙碌线程中去
    int create();                              //创建线程池中的线程池
};
#endif