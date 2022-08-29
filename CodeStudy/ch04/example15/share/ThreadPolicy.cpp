
#include "../include/ThreadPolicy.h"

ThreadPolicy::ThreadPolicy()
{
    cout << "ThreadPolicy()构造函数" << endl;
}

ThreadPolicy::~ThreadPolicy()
{
    cout << "~ThreadPolicy()析构函数" << endl;
}

/**
 * @brief 获取线程调度策略
 *
 * @param attr
 * @return int
 */
int ThreadPolicy::getThreadPolicy(pthread_attr_t *attr)
{
    int policy;                                           //线程调度策略
    int res = pthread_attr_getschedpolicy(attr, &policy); //获取线程调度策略
    assert(res == 0);                                     //获取线程调度成功
    switch (policy)
    {
    case SCHED_FIFO: //先来先服务调度策略
        printf("policy=SCHED_FIFO\n");
        break;
    case SCHED_RR: //时间片轮转(轮循)调度策略
        printf("policy=SCHED_RR\n");
        break;
    case SCHED_OTHER: //分时调度策略
        printf("policy=SCHED_OTHER\n");
        break;
    default:
        printf("policy=UNKNOWN\n");
        break;
    }
    return policy;
}

/**
 * @brief 显示线程指定调度策略下的最大可用优先级和最小可用优先级
 *
 * @param attr
 * @param policy
 */
void ThreadPolicy::showThreadPriority(pthread_attr_t *attr, int policy)
{
    int priority = sched_get_priority_max(policy); //获取线程指定调度策略下可用最大线程优先级
    assert(priority != -1);                        //获取线程优先级成功
    printf("max_priority=%d\n", priority);
    priority = sched_get_priority_min(policy); //获取线程指定调度策略下可用最小线程优先级
    assert(priority != -1);
    printf("min_priority=%d\n", priority);
}

/**
 * @brief 获取当前线程的线程优先级
 *
 * @param attr
 */
int ThreadPolicy::getThreadPriority(pthread_attr_t *attr)
{
    struct sched_param param;                           //线程优先级结构体
    int res = pthread_attr_getschedparam(attr, &param); //获取线程优先级
    assert(res == 0);                                   //获取线程优先级成功,返回0
    int priority = param.sched_priority;                //获取线程优先级
    printf("priority=%d\n", priority);
    return priority;
}

/**
 * @brief 设置线程调度策略
 *
 * @param attr 线程属性
 * @param policy 线程调度策略
 */
void ThreadPolicy::setThreadPolicy(pthread_attr_t *attr, int policy)
{
    int res = pthread_attr_setschedpolicy(attr, policy);        //设置线程调度策略
    assert(res == 0);                                           //设置成功返回0
    pthread_attr_setinheritsched(attr, PTHREAD_EXPLICIT_SCHED); //要使优先级其作用必须要有这句话
}

/**
 * @brief 设置线程优先级
 *
 * @param attr
 * @param priority
 */
void ThreadPolicy::setThreadPriority(pthread_attr_t *attr, int priority)
{
    struct sched_param param;                                   //线程优先级结
    param.sched_priority = priority;                            //设置线程优先级
    int res = pthread_attr_setschedparam(attr, &param);         //设置线程优先级
    assert(res == 0);                                           //设置成功返回0
    pthread_attr_setinheritsched(attr, PTHREAD_EXPLICIT_SCHED); //要使优先级其作用必须要有这句话
}
