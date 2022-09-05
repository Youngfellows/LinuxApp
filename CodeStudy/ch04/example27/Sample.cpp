#include "./include/Sample.h"

//全局变量
pthread_mutex_t mutex;   //互斥锁
pthread_rwlock_t rwlock; //读写锁

//全局变量
int global = 1024;

/**
 * @brief 互斥锁和读写锁速度大PK
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    mutexVer();
    rdlockVer();
    cout << endl;
}

/**
 * @brief 互斥锁线程
 *
 */
void mutexVer()
{
    printf("mutexVer():: ...");
    pthread_t threadId1; //线程ID
    pthread_t threadId2; //线程ID
    int ret;
    struct timeval start;                                               //系统开始时间
    struct timeval end;                                                 //系统结束时间
    pthread_mutex_init(&mutex, nullptr);                                //初始化互斥锁
    gettimeofday(&start, nullptr);                                      //获取系统开始时间
    ret = pthread_create(&threadId1, nullptr, threadFunctin1, nullptr); //创建线程1
    if (ret != 0)
    {
        printf("pthread create failed:%s\n", strerror(ret)); //打印错误信息
        exit(1);                                             //结束进程
    }
    ret = pthread_create(&threadId2, nullptr, threadFunctin2, nullptr); //创建线程2
    if (ret != 0)
    {
        printf("pthread create failed:%s\n", strerror(ret)); //打印错误信息
        exit(1);                                             //结束进程
    }
    ret = pthread_join(threadId1, nullptr); //等待子线程1结束
    if (ret != 0)
    {
        printf("wait thread done error:%s\n", strerror(ret));
    }
    ret = pthread_join(threadId2, nullptr); //等待子线程1结束
    if (ret != 0)
    {
        printf("wait thread done error:%s\n", strerror(ret));
    }

    pthread_mutex_destroy(&mutex); //销毁互斥锁

    gettimeofday(&end, nullptr);                                                                 //获取系统结束时间
    long long totalTime = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec); //微妙
    totalTime /= 1000;                                                                           //毫秒
    printf("total mutex time is %lld ms\n", totalTime);
}

/**
 * @brief 读写锁线程
 *
 */
void rdlockVer()
{
    printf("rdlockVer():: ...");
    pthread_t threadId1; //线程ID
    pthread_t threadId2; //线程ID
    int ret;
    struct timeval start; //系统开始时间
    struct timeval end;   //系统结束时间
    // pthread_mutex_init(&mutex, nullptr);                                //初始化互斥锁
    pthread_rwlock_init(&rwlock, nullptr);                              //初始化读写锁
    gettimeofday(&start, nullptr);                                      //获取系统开始时间
    ret = pthread_create(&threadId1, nullptr, threadFunctin3, nullptr); //创建线程1
    if (ret != 0)
    {
        printf("pthread create failed:%s\n", strerror(ret)); //打印错误信息
        exit(1);                                             //结束进程
    }
    ret = pthread_create(&threadId2, nullptr, threadFunctin4, nullptr); //创建线程2
    if (ret != 0)
    {
        printf("pthread create failed:%s\n", strerror(ret)); //打印错误信息
        exit(1);                                             //结束进程
    }
    ret = pthread_join(threadId1, nullptr); //等待子线程1结束
    if (ret != 0)
    {
        printf("wait thread done error:%s\n", strerror(ret));
    }
    ret = pthread_join(threadId2, nullptr); //等待子线程1结束
    if (ret != 0)
    {
        printf("wait thread done error:%s\n", strerror(ret));
    }

    pthread_rwlock_destroy(&rwlock); //销毁读写锁

    gettimeofday(&end, nullptr);                                                                 //获取系统结束时间
    long long totalTime = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec); //微妙
    totalTime /= 1000;                                                                           //毫秒
    printf("total mutex time is %lld ms\n", totalTime);
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
 * @param para
 * @return void*
 */
void *threadFunctin1(void *para)
{
    cout << __FUNCTION__ << " ,Start ..." << endl;
    volatile int a;
    for (int i = 0; i < 10000000; i++)
    {
        pthread_mutex_lock(&mutex);   //互斥锁加锁
        a = global;                   //只读全局变量
        pthread_mutex_unlock(&mutex); //互斥锁解锁
    }
    cout << __FUNCTION__ << " ,End ..." << endl;
    pthread_exit((void *)0);
}

/**
 * @brief 线程回调函数
 *
 * @param para
 * @return void*
 */
void *threadFunctin2(void *para)
{
    cout << __FUNCTION__ << " ,Start ..." << endl;
    volatile int b;
    for (int i = 0; i < 10000000; i++)
    {
        pthread_mutex_lock(&mutex);   //互斥锁加锁
        b = global;                   //只读全局变量
        pthread_mutex_unlock(&mutex); //互斥锁解锁
    }
    cout << __FUNCTION__ << " ,End ..." << endl;
    pthread_exit(nullptr);
}

/**
 * @brief 线程回调函数
 *
 * @param para
 * @return void*
 */
void *threadFunctin3(void *para)
{
    cout << __FUNCTION__ << " ,Start ..." << endl;
    volatile int a;
    for (int i = 0; i < 10000000; i++)
    {
        pthread_rwlock_rdlock(&rwlock); //读写锁上读锁
        a = global;                     //只读全局变量
        pthread_rwlock_unlock(&rwlock); //读写锁释放锁
    }
    cout << __FUNCTION__ << " ,End ..." << endl;
    pthread_exit((void *)0);
}

/**
 * @brief 线程回调函数
 *
 * @param para
 * @return void*
 */
void *threadFunctin4(void *para)
{
    cout << __FUNCTION__ << " ,Start ..." << endl;
    volatile int b;
    for (int i = 0; i < 10000000; i++)
    {
        pthread_rwlock_rdlock(&rwlock); //读写锁上读锁
        b = global;                     //只读全局变量
        pthread_rwlock_unlock(&rwlock); //读写锁释放锁
    }
    cout << __FUNCTION__ << " ,End ..." << endl;
    pthread_exit(nullptr);
}