#include "./include/Sample.h"

/**
 * @brief 获取线程调度策略和设置线程优先级
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    int uid;              //用户ID
    pthread_t threadId1;  //线程ID
    pthread_t threadId2;  //线程ID
    pthread_t threadId3;  //线程ID
    pthread_attr_t attr1; //线程属性结构体
    pthread_attr_t attr2; //线程属性结构体
    pthread_attr_t attr3; //线程属性结构体
    int ret1;             //线程创建结果
    int ret2;             //线程创建结果
    int ret3;             //线程创建结果
    // struct sched_param param; //线程优先级结构体

    uid = getuid(); //获取用户ID
    if (uid == 0)
    {
        printf("当前用户是root\n");
    }
    else
    {
        printf("当前用户不是root\n");
    }

    pthread_attr_init(&attr1); //初始化线程属性结构体
    pthread_attr_init(&attr2); //初始化线程属性结构体
    pthread_attr_init(&attr3); //初始化线程属性结构体

    int policy = ThreadPolicy::getThreadPolicy(&attr1); //获取线程调度策略
    printf("当前设置的线程最大、最小优先级:\n");
    ThreadPolicy::showThreadPriority(&attr1, policy); //获取指定调度策略下可设置的线程最大、最小优先级
    printf("当前设置的线程优先级\n");
    int priority = ThreadPolicy::getThreadPriority(&attr1);
    printf("priority=%d\n", priority);

    printf("显示SCHED_RR调度策略下的优先级:\n");
    ThreadPolicy::showThreadPriority(&attr1, SCHED_RR);

    printf("显示SCHED_FIFO调度策略下的优先级:\n");
    ThreadPolicy::showThreadPriority(&attr1, SCHED_FIFO);

    //设置线程调度策略SCHED_FIFO
    // printf("设置线程调度策略SCHED_FIFO\n");
    ThreadPolicy::setThreadPolicy(&attr1, SCHED_FIFO); //设置线程调度策略SCHED_FIFO
    // policy = ThreadPolicy::getThreadPolicy(&attr1);    //获取线程调度策略
    // printf("设置线程调度策略SCHED_FIFO的线程优先级\n");
    ThreadPolicy::setThreadPriority(&attr1, 55); //设置线程调度策略SCHED_FIFO的线程优先级
    // ThreadPolicy::showThreadPriority(&attr1, policy);       //获取指定调度策略下可设置的线程最大、最小优先级
    // int priority = ThreadPolicy::getThreadPriority(&attr1); //获取指定调度策略下当前线程优先级
    // printf("调度策略SCHED_FIFO的线程优先级:priority=%d\n", priority);

    //设置线程调度策略SCHED_RR
    ThreadPolicy::setThreadPolicy(&attr2, SCHED_FIFO); //设置线程调度策略SCHED_RR
    ThreadPolicy::setThreadPriority(&attr2, 38);       //设置线程优先级

    ret1 = pthread_create(&threadId1, &attr1, threadFunction1, nullptr); //创建线程1
    if (ret1 != 0)
    {
        handle_error_en(ret1, "pthread_create failed");
    }
    ret2 = pthread_create(&threadId2, &attr2, threadFunction2, nullptr); //创建线程2
    if (ret2 != 0)
    {
        handle_error_en(ret2, "pthread_create failed");
    }
    ret3 = pthread_create(&threadId3, &attr3, threadFunction3, nullptr); //创建线程3
    if (ret3 != 0)
    {
        handle_error_en(ret3, "pthread_create failed");
    }

    pthread_join(threadId1, nullptr); //等待线程1执行完成
    pthread_join(threadId2, nullptr); //等待线程2执行完成
    pthread_join(threadId3, nullptr); //等待线程3执行完成

    pthread_attr_destroy(&attr1); //销毁线程属性结构体
    pthread_attr_destroy(&attr2); //销毁线程属性结构体
    pthread_attr_destroy(&attr3); //销毁线程属性结构体

    cout << endl;
}

/**
 * @brief 线程1回调函数
 *
 * @param para
 * @return void*
 */
void *threadFunction1(void *para)
{
    sleep(1);      //阻塞1秒线程1
    pthread_t tid; //获取线程ID
    int res;
    int policy;                                        //线程调度策略
    struct sched_param param;                          //线程优先级结构体参数
    int priority;                                      //当前线程优先级
    tid = pthread_self();                              //获取线程ID
    res = pthread_getschedparam(tid, &policy, &param); //获取线程调度策略和线程优先级
    if (res != 0)
    {
        handle_error_en(res, "pthread_getschedparam failed");
    }

    if (policy == SCHED_OTHER) //分时调度策略
    {
        printf("线程1的Thread ID:%ld,分时调度策略,SCHED_OTHER\n", tid);
    }
    else if (policy == SCHED_FIFO) //先来先服务调度策略
    {
        printf("线程1的Thread ID:%ld,先来先服务调度策略,SCHED_FIFO\n", tid);
    }
    else if (policy == SCHED_RR) //实时调度策略,时间片轮转
    {
        printf("线程1的Thread ID:%ld,实时调度策略,时间片轮转,SCHED_RR\n", tid);
    }
    else
    {
        printf("线程1的Thread ID:%ld,未知的线程调度策略\n", tid);
    }

    //获取当前线程优先级
    priority = param.sched_priority;
    printf("线程1的Thread ID:%ld,当前线程优先级,priority:%d\n", tid, priority);

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 5000000; j++)
        {
        }
        printf("线程1的Thread ID:%ld,%d\n", tid, i);
    }
    printf("线程1退出,Thread ID:%ld\n", tid);
    pthread_exit(0); //结束线程1
}

/**
 * @brief 线程2回调函数
 *
 * @param para
 * @return void*
 */
void *threadFunction2(void *para)
{
    sleep(1);      //阻塞1秒线程2
    pthread_t tid; //获取线程ID
    int res;
    int policy;                                        //线程调度策略
    struct sched_param param;                          //线程优先级结构体参数
    int priority;                                      //当前线程优先级
    tid = pthread_self();                              //获取线程ID
    res = pthread_getschedparam(tid, &policy, &param); //获取线程调度策略和线程优先级
    if (res != 0)
    {
        handle_error_en(res, "pthread_getschedparam failed");
    }

    if (policy == SCHED_OTHER) //分时调度策略
    {
        printf("线程2的Thread ID:%ld,分时调度策略,SCHED_OTHER\n", tid);
    }
    else if (policy == SCHED_FIFO) //先来先服务调度策略
    {
        printf("线程2的Thread ID:%ld,先来先服务调度策略,SCHED_FIFO\n", tid);
    }
    else if (policy == SCHED_RR) //实时调度策略,时间片轮转
    {
        printf("线程2的Thread ID:%ld,实时调度策略,时间片轮转,SCHED_RR\n", tid);
    }
    else
    {
        printf("线程2的Thread ID:%ld,未知的线程调度策略\n", tid);
    }

    //获取当前线程优先级
    priority = param.sched_priority;
    printf("线程2的Thread ID:%ld,当前线程优先级,priority:%d\n", tid, priority);

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 5000000; j++)
        {
        }
        printf("线程2的Thread ID:%ld,%d\n", tid, i);
    }
    printf("线程2退出,Thread ID:%ld\n", tid);
    pthread_exit(0); //结束线程2
}

/**
 * @brief 线程3回调函数
 *
 * @param para
 * @return void*
 */
void *threadFunction3(void *para)
{
    sleep(1);      //阻塞1秒线程3
    pthread_t tid; //获取线程ID
    int res;
    int policy;                                        //线程调度策略
    struct sched_param param;                          //线程优先级结构体参数
    int priority;                                      //当前线程优先级
    tid = pthread_self();                              //获取线程ID
    res = pthread_getschedparam(tid, &policy, &param); //获取线程调度策略和线程优先级
    if (res != 0)
    {
        handle_error_en(res, "pthread_getschedparam failed");
    }

    if (policy == SCHED_OTHER) //分时调度策略
    {
        printf("线程3的Thread ID:%ld,分时调度策略,SCHED_OTHER\n", tid);
    }
    else if (policy == SCHED_FIFO) //先来先服务调度策略
    {
        printf("线程3的Thread ID:%ld,先来先服务调度策略,SCHED_FIFO\n", tid);
    }
    else if (policy == SCHED_RR) //实时调度策略,时间片轮转
    {
        printf("线程3的Thread ID:%ld,实时调度策略,时间片轮转,SCHED_RR\n", tid);
    }
    else
    {
        printf("线程3的Thread ID:%ld,未知的线程调度策略\n", tid);
    }

    //获取当前线程优先级
    priority = param.sched_priority;
    printf("线程3的Thread ID:%ld,当前线程优先级,priority:%d\n", tid, priority);

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 5000000; j++)
        {
        }
        printf("线程3的Thread ID:%ld,%d\n", tid, i);
    }
    printf("线程3退出,Thread ID:%ld\n", tid);
    pthread_exit(0); //结束线程3
}

void test2()
{
    cout << "test2():: ..." << endl;
    cout << endl;
}

void test3()
{
    cout << "test3():: ..." << endl;
    cout << endl;
}

void test4()
{
    cout << "test4():: ..." << endl;
    cout << endl;
}