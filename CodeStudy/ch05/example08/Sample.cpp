#include "./include/Sample.h"

/**
 * @brief 设置C++ 11 线程调度策略和线程优先级
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    std::thread myThread(threadFunction);                                              //初始化线程对象
    ThreadSched threadSched(myThread.native_handle(), SCHED_FIFO, 41, "Speex Thread"); //获取并设置线程调度策略和优先级
    myThread.detach();                                                                 //分离线程
    pthread_exit(nullptr);                                                             //结束主线程,进程继续执行
    cout << "主线程退出了,这一句将不会执行 ..." << endl;
    cout << endl;
}

/**
 * @brief 线程回调函数
 *
 */
void threadFunction()
{
    pthread_t threadId = pthread_self();
    std::cout << __FUNCTION__ << " 子线程执行了,Thread ID:" << std::this_thread::get_id() << std::endl;
    sched_param currSchedParams; //当前调度优先级
    int currPolicy = 0;          //当前调度策略
    
    if (pthread_getschedparam(threadId, &currPolicy, &currSchedParams)) // C++11 获取当前线程调度策略和线程优先级
    {
        std::cout << __FUNCTION__ << " Failed to pthread_getschedparam: ERROR " << strerror(errno) << std::endl;
        std::cout << __FUNCTION__ << " setconfiguration failed current configuration Thread [" << threadId
                  << "] currPolicy [" << currPolicy << "] and PRIORITY ["
                  << currSchedParams.sched_priority << "]" << std::endl;
    }
    else
    {
        std::cout << __FUNCTION__ << " setconfiguration successfull current configuration Thread [" << threadId
                  << "] currPolicy [" << currPolicy << "] and PRIORITY ["
                  << currSchedParams.sched_priority << "]" << std::endl;
    }

    switch (currPolicy)
    {
    case SCHED_OTHER:
        std::cout << __FUNCTION__ << " SCHED_OTHER" << std::endl;
        break;
    case SCHED_FIFO:
        std::cout << __FUNCTION__ << " SCHED_FIFO" << std::endl;
        break;
    case SCHED_RR:
        std::cout << __FUNCTION__ << " SCHED_RR" << std::endl;
        break;
    default:
        std::cout << __FUNCTION__ << " UNKONWN" << std::endl;
        break;
    }
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