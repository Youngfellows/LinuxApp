#include "../include/ThreadPool.h"

//静态成员初始化
std::shared_ptr<vector<Task *>> ThreadPool::mVecTaskLit = std::make_shared<vector<Task *>>();
bool ThreadPool::shutdown = false;
pthread_mutex_t ThreadPool::mThreadMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t ThreadPool::mThreadCond = PTHREAD_COND_INITIALIZER;

ThreadPool::ThreadPool(int threadNum)
{
    cout << __FUNCTION__ << " ,构造函数 ..." << endl;
    this->mThreadNum = threadNum;
    printf("将会创建%d个线程\n", threadNum);
    create();
}

ThreadPool::~ThreadPool()
{
    cout << __FUNCTION__ << " ,析构函数 ..." << endl;
}

/**
 * @brief 创建线程池中的线程池
 *
 * @return int
 */
int ThreadPool::create()
{
    int ret;
    this->mThreadId = new pthread_t[mThreadNum]; //动态申请内存,创建线程列表数组,指针
    for (int i = 0; i < mThreadNum; i++)
    {
        ret = pthread_create(&mThreadId[i], nullptr, threadFunc, nullptr); //创建线程
        if (ret != 0)
        {
            printf("创建线程错误:%s\n", strerror(ret));
            exit(0); //结束进程
        }
    }
    return 0; //创建线程池成功返回0
}

/**
 * @brief 把任务添加到任务队列中
 * @brief 往任务队列里添加添加任务并发出线程同步信号
 * @param task 要添加的任务
 * @return int 添加是否成功返回
 */
int ThreadPool::addTask(Task *task)
{
    pthread_mutex_lock(&mThreadMutex); //互斥锁加锁
    mVecTaskLit->push_back(task);
    pthread_mutex_unlock(&mThreadMutex); //互斥锁释放锁
    pthread_cond_signal(&mThreadCond);   //向线程发送信号,使等待的线程继续往下执行
    return 0;
}

/**
 * @brief 使线程池中的所有线程都退出
 * @brief 停止所有线程
 * @return int
 */
int ThreadPool::stopAll()
{
    //避免重复调用
    if (shutdown)
    {
        return -1;
    }
    printf("停止全部线程\n");

    //唤醒所有等待的线程,线程池要销毁了
    shutdown = true;
    pthread_cond_broadcast(&mThreadCond);

    //清理僵尸进程
    for (int i = 0; i < mThreadNum; i++)
    {
        pthread_join(mThreadId[i], nullptr); //等待线程执行结束
    }

    //释放内存
    delete[] mThreadId;
    mThreadId = nullptr;

    //销毁互斥锁和条件变量
    pthread_mutex_destroy(&mThreadMutex);
    pthread_cond_destroy(&mThreadCond);

    return 0;
}

/**
 * @brief 获取当前任务队列中的任务数
 *
 * @return int
 */
int ThreadPool::getTaskSize()
{
    return mVecTaskLit->size();
}

/**
 * @brief 新线程的线程回调函数
 *
 * @param threadData
 * @return void*
 */
void *ThreadPool::threadFunc(void *threadData)
{
    pthread_t tid = pthread_self(); //获取子线程线程ID
    while (true)
    {
        pthread_mutex_lock(&mThreadMutex); //互斥锁上锁
        //如果任务队列为空,等待新的任务进入任务队列
        while (mVecTaskLit->size() == 0 && !shutdown)
        {
            pthread_cond_wait(&mThreadCond, &mThreadMutex); //阻塞并释放锁,接收条件变量的唤醒信号,然后才继续往下执行
        }

        //关闭线程
        if (shutdown)
        {
            pthread_mutex_unlock(&mThreadMutex); //互斥锁释放锁
            printf("[tid: %lu]\t exit\n", pthread_self());
            pthread_exit(nullptr); //退出子线程
        }

        //线程运行,取出一个任务并运行处理之
        printf("[tid: %lu]\t run: \n", tid);
        std::vector<Task *>::iterator iter = mVecTaskLit->begin();
        Task *task = *iter;
        if (iter != mVecTaskLit->end())
        {
            task = *iter;
            mVecTaskLit->erase(iter); //移除已经运行的任务
        }
        pthread_mutex_unlock(&mThreadMutex); //互斥锁释放锁

        task->run(); //执行任务
        printf("[tid: %lu]\t idle\n", tid);
    }
}

/**
 * @brief 线程执行结束后,把自己放入空闲线程中去
 *
 * @param tid
 * @return int
 */
int ThreadPool::moveToIdle(pthread_t tid)
{
    return 0;
}

/**
 * @brief 移入到忙碌线程中去
 *
 */
int ThreadPool::moveToBusy(pthread_t tid)
{
    return 0;
}