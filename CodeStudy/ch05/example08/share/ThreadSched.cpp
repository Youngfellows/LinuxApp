#include "../include/ThreadSched.h"

ThreadSched::ThreadSched(pthread_t threadId, const int policy, const int priority, std::string name)
{
    this->mThreadName = name;
    this->mThreadId = threadId;
    this->mPolicy = policy;
    this->mSchedParam.sched_priority = priority;
    sched_param currSchedParams; //当前调度优先级
    int currPolicy = 0;          //当前调度策略
    // mThread.native_handle()
    if (pthread_getschedparam(mThreadId, &currPolicy, &currSchedParams)) // C++11 获取当前线程调度策略和线程优先级
    {
        std::cout << "Failed to pthread_getschedparam: ERROR" << strerror(errno) << "";
    }
    std::cout << "Current configuration Thread [" << mThreadId
              << "] currPolicy [" << currPolicy << "] and PRIORITY ["
              << currSchedParams.sched_priority << "]" << std::endl;

    std::cout << "Trying to set configuration as Thread  [" << mThreadId
              << "] currPolicy [" << mPolicy << "] and PRIORITY ["
              << mSchedParam.sched_priority << "]";

    int iRet = -1;
    iRet = pthread_setschedparam(mThreadId, mPolicy, &mSchedParam); // C++11 设置线程优先级                                                          //设置线程优先级结构返回
    if (iRet)
    {
        switch (iRet)
        {
        case ESRCH: //指定ID的线程不存在
            std::cout << "No thread with the ID thread could be found" << std::endl;
            break;
        case EINVAL: //调度策略不是可识别的策略，或者优先级参数对策略没有意义
            std::cout << "policy is not a recognized policy, or param does not make sense for the policy." << std::endl;
            break;
        case EPERM: //调用方没有设置指定调度策略和优先级参数的适当权限
            std::cout << "The caller does not have appropriate privileges to set the specified scheduling policy and parameters." << std::endl;
            break;
        case ENOTSUP: //试图将调度策略或优先级参数设置为不受支持的值
            std::cout << "attempt was made to set the policy or scheduling parameters to an unsupported value" << std::endl;
            break;
        default:
            break;
        }
        std::cout << "Return value [" << iRet << "] Failed to pthread_setschedparam: ERROR" << strerror(errno) << "";
    }

    if (pthread_getschedparam(mThreadId, &currPolicy, &currSchedParams)) // C++11 获取当前线程调度策略和线程优先级
    {
        std::cout << "Failed to pthread_getschedparam: ERROR " << strerror(errno) << std::endl;
    }
    std::cout << "setconfiguration successfull current configuration Thread [" << mThreadId
              << "] currPolicy [" << currPolicy << "] and PRIORITY ["
              << currSchedParams.sched_priority << "]" << std::endl;

    switch (currPolicy)
    {
    case SCHED_OTHER:
        std::cout << "Current Sched Policy is SCHED_OTHER" << std::endl;
        break;
    case SCHED_FIFO:
        std::cout << "Current Sched Policy is SCHED_FIFO" << std::endl;
        break;
    case SCHED_RR:
        std::cout << "Current Sched Policy is SCHED_RR" << std::endl;
        break;
    default:
        std::cout << "Current Sched Policy UNKONWN" << std::endl;
        break;
    }
}

ThreadSched::~ThreadSched()
{
    cout << "~ThreadSched()析构函数" << endl;
}
