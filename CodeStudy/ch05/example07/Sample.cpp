#include "./include/Sample.h"

/**
 * @brief 1. C++ 11 设置线程调度策略和线程优先级
 * @brief 2. 必须要以root模式运行程序,否则无法设置调度策略
 */
void test1()
{
    cout << "test1():: ..." << endl;
    std::thread::id tid = std::this_thread::get_id(); //获取线程ID
    struct sched_param sch;                           //线程优先级结构体
    int policy;                                       //线程调度策略
    std::thread myThread(threadFunction);

    pthread_t threadId = myThread.native_handle();
    cout << "主线程执行了,Thread ID:" << tid << ",threadId:" << threadId << endl;

    pthread_getschedparam(threadId, &policy, &sch);
    printf("主线程执行了,myThread子线程,policy:%d,sched_priority:%d\n", policy, sch.sched_priority);
    sch.sched_priority = 51;
    // if (pthread_setschedparam(threadId, SCHED_FIFO, &sch))
    // {
    //     printf("设置线程调度策略和优先级错误: %s\n", strerror(errno));
    // }
    if (pthread_setschedparam(threadId, SCHED_RR, &sch))
    {
        printf("设置线程调度策略和优先级错误: %s\n", strerror(errno));
    }
    myThread.detach();     //分离线程
    pthread_exit(nullptr); //主线程退出
    cout << "主线程退出了,这句将不执行 ..." << endl;

    cout << endl;
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

/**
 * @brief 线程回调函数
 *
 */
void threadFunction()
{
    std::thread::id tid = std::this_thread::get_id(); //获取线程ID
    cout << "子线程Thread ID:" << tid << endl;
    struct sched_param sch; //线程优先级结构体
    int policy;             //线程调度策略
    pthread_getschedparam(pthread_self(), &policy, &sch);
    printf("子线程,policy:%d,sched_priority:%d\n", policy, sch.sched_priority);

    if (policy == SCHED_OTHER) //分时调度策略
    {
        printf("子线程,分时调度策略,SCHED_OTHER\n");
    }
    else if (policy == SCHED_FIFO) //先来先服务调度策略
    {
        printf("子线程,先来先服务调度策略,SCHED_FIFO\n");
    }
    else if (policy == SCHED_RR) //实时调度策略,时间片轮转
    {
        printf("子线程,实时调度策略,时间片轮转,SCHED_RR\n");
    }
    else
    {
        printf("子线程,未知的线程调度策略\n");
    }
}