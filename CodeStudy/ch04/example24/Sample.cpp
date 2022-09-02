#include "./include/Sample.h"

//静态初始化互斥锁
// pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

//动态初始化互斥锁
pthread_mutex_t mutex;

//共享全局变量
int global = 0;

/**
 * @brief 1. 使用互斥锁实现线程同步
 * @brief 2. 静态初始化互斥锁
 */
void test1()
{
    cout << "test1():: ..." << endl;
    pthread_t tid1;                      //线程ID
    pthread_t tid2;                      //线程ID
    int ret;                             //线程执行结果
    pthread_mutex_init(&mutex, nullptr); //动态初始化互斥锁
    for (int i = 0; i < 10; i++)         //循环10次
    {
        ret = pthread_create(&tid1, nullptr, threadFunction1, nullptr); //创建线程1
        if (ret != 0)
        {
            printf("create new thread error: %s\n", strerror(ret)); //打印错误信息
            exit(1);                                                //结束进程
        }
        ret = pthread_create(&tid2, nullptr, threadFunction2, nullptr); //创建线程2
        if (ret != 0)
        {
            printf("cretae new thread error: %s\n", strerror(ret)); //打印错误信息
            exit(1);                                                //结束进程
        }
        ret = pthread_join(tid1, nullptr); //等待子线程1结束
        if (ret != 0)
        {
            printf("等待子线程1结束错误: %s\n", strerror(ret));
            exit(1);
        }
        ret = pthread_join(tid2, nullptr); //等待子线程2结束
        if (ret != 0)
        {
            printf("等待子线程2结束错误: %s\n", strerror(ret));
            exit(1);
        }
        printf("global=%d\n", global); //打印2个线程累加后的全局变量
        global = 0;                    //置0
    }
    pthread_mutex_destroy(&mutex); //销毁互斥锁
    cout << endl;
}

/**
 * @brief 线程1回调函数
 *
 * @param para 向线程传递的参数
 * @return void*
 */
void *threadFunction1(void *para)
{
    pthread_t tid = pthread_self(); //获取线程ID
    printf("开始执行子线程1,Thread ID:%ld\n", tid);
    for (int i = 0; i < 10000000; i++)
    {
        pthread_mutex_lock(&mutex); //互斥锁加锁
        global++;
        pthread_mutex_unlock(&mutex); //互斥锁解锁
    }
    pthread_exit((void *)0); //结束子线程
}

/**
 * @brief 线程2回调函数
 *
 * @param para 向线程传递的参数
 * @return void*
 */
void *threadFunction2(void *para)
{
    pthread_t tid = pthread_self(); //获取线程ID
    printf("开始执行子线程2,Thread ID:%ld\n", tid);
    for (int i = 0; i < 10000000; i++)
    {
        pthread_mutex_lock(&mutex); //互斥锁加锁
        global++;
        pthread_mutex_unlock(&mutex); //互斥锁解锁
    }
    pthread_exit((void *)0); //结束子线程
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