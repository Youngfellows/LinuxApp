#ifndef THREAD_SCHED_H
#define THREAD_SCHED_H

#include "./Global.h"

/**
 * @brief C++ 11线程调度策略
 *
 */
class ThreadSched
{
private:
    pthread_t mThreadId;     //线程ID
    int mPolicy;             //线程调度策略
    sched_param mSchedParam; //线程优先级结构体
    std::string mThreadName; //线程名称
public:
    ThreadSched(pthread_t threadId, const int policy, const int priority, std::string name);
    ~ThreadSched();
};
#endif