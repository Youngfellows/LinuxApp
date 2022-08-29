#include "./include/Sample.h"

/**
 * @brief 获取三种调度策略下,可设置的最大和最小优先级
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    //获取SCHED_OTHER分时调度策略可设置的最低优先级和最高优先级
    printf("SCHED_OTHRE 调度策略下优先级范围:%d - %d\n", sched_get_priority_min(SCHED_OTHER), sched_get_priority_max(SCHED_OTHER));
    //获取SCHED_FIFO先来先服务调度策略可设置的最低优先级和最高优先级
    printf("SCHED_FIFO 调度策略下优先级范围:%d - %d\n", sched_get_priority_min(SCHED_FIFO), sched_get_priority_max(SCHED_FIFO));
    //获取SCHED_RR实时调度策略,时间片轮转可设置的最低优先级和最高优先级
    printf("SCHED_RR 调度策略下优先级范围:%d - %d\n", sched_get_priority_min(SCHED_RR), sched_get_priority_max(SCHED_RR));
    cout << endl;
}

/**
 * @brief 设置线程的调度策略和优先级
 *
 */
void test2()
{
    cout << "test2():: ..." << endl;
    int uid;                  //用户ID
    pthread_t threadId1;      //线程ID
    pthread_t threadId2;      //线程ID
    pthread_t threadId3;      //线程ID
    pthread_attr_t attr1;     //线程属性结构体
    pthread_attr_t attr2;     //线程属性结构体
    pthread_attr_t attr3;     //线程属性结构体
    int ret1;                 //线程创建结果
    int ret2;                 //线程创建结果
    int ret3;                 //线程创建结果
    struct sched_param param; //线程优先级结构体

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

    //设置线程调度策略和线程优先级
    param.sched_priority = 51;
    pthread_attr_setschedpolicy(&attr1, SCHED_RR);                // 设置SCHED_RR实时调度策略,时间片轮转
    pthread_attr_setschedparam(&attr1, &param);                   //设置线程优先级
    pthread_attr_setinheritsched(&attr1, PTHREAD_EXPLICIT_SCHED); //要使优先级其作用必须要有这句话

    param.sched_priority = 61;
    pthread_attr_setschedpolicy(&attr2, SCHED_RR);                // 设置SCHED_RR实时调度策略,时间片轮转
    pthread_attr_setschedparam(&attr2, &param);                   //设置线程优先级
    pthread_attr_setinheritsched(&attr2, PTHREAD_EXPLICIT_SCHED); //要使优先级其作用必须要有这句话

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