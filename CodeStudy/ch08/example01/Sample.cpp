#include "./include/Sample.h"

/**
 * @brief 全局变量,信号量
 *
 */
sem_t mutex;

/**
 * @brief 使用信号量实现线程同步
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    sem_init(&mutex, 0, 0); //初始化信号量
    pthread_t thread[3];    // 3个线程
    int number = 5;         //传递的数据

    pthread_create(&thread[0], nullptr, semWaitFunction, &number); //创建线程,并向线程传递参数
    printf("thread semWaitFunction\n");

    pthread_create(&thread[2], nullptr, semTimedWaitFunction, &number); //创建线程,并向线程传递参数
    printf("thread semTimedWaitFunction\n");

    sleep(4); //休眠4秒

    pthread_create(&thread[1], nullptr, semPostFunction, &number); //创建线程,并向线程传递参数
    printf("thread semPostFunction\n");

    pthread_join(thread[0], nullptr); //等待线程结束
    pthread_join(thread[1], nullptr); //等待线程结束
    pthread_join(thread[2], nullptr); //等待线程结束

    //销毁信号量
    sem_destroy(&mutex);
    cout << endl;
}

/**
 * @brief 获取当前时间精确到毫秒
 *
 * @return int64_t
 */
int64_t getTimeMsec()
{
    struct timeval tv;
    gettimeofday(&tv, nullptr); //获取系统当前时间
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

/**
 * @brief 线程回调函数
 *
 * @param arg 向线程传递的参数
 * @return void*
 */
void *semWaitFunction(void *arg)
{
    printf("set wait\n");
    sem_wait(&mutex);
    printf("set wait success\n");
    int *running = (int *)arg; //获取线程参数
    printf("semWaitFunction running: %d\n", *running);
    return nullptr;
}

/**
 * @brief 线程回调函数
 *
 * @param arg 向线程传递的参数
 * @return void*
 */
void *semTimedWaitFunction(void *arg)
{
    timespec timewait;
    timewait.tv_sec = getTimeMsec() / 1000 + 2;
    timewait.tv_nsec = 0;
    printf("set timed wait\n");
    int ret = sem_timedwait(&mutex, &timewait);
    printf("sem_timedwait,ret:%d\n", ret);
    int *running = (int *)arg; //获取线程参数
    printf("semTimedWaitFunction running: %d\n", *running);
    return nullptr;
}

/**
 * @brief 线程回调函数
 *
 * @param arg 向线程传递的参数
 * @return void*
 */
void *semPostFunction(void *arg)
{
    printf("semPostFunction running\n");
    printf("sem post\n");
    int *a = (int *)arg;
    *a = 1024;
    sem_post(&mutex);
    sem_post(&mutex);
    return nullptr;
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