#ifndef THREAD_POLICY_H
#define THREAD_POLICY_H

#include "./Global.h"

/**
 * @brief 获取线程调度策略和线程优先级
 *
 */
class ThreadPolicy
{
public:
    ThreadPolicy();
    ~ThreadPolicy();
    static int getThreadPolicy(pthread_attr_t *attr);                  //获取线程调度策略
    static void showThreadPriority(pthread_attr_t *attr, int policy);  //显示线程指定调度策略下的最大可用优先级和最小可用优先级
    static int getThreadPriority(pthread_attr_t *attr);                //获取当前线程的线程优先级
    static void setThreadPolicy(pthread_attr_t *attr, int policy);     //设置线程调度策略
    static void setThreadPriority(pthread_attr_t *attr, int priority); //设置线程优先级
};
#endif