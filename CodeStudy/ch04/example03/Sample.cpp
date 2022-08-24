#include "./include/Sample.h"

//静态初始化互斥锁
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int count = 0; //共享数据

/**
 * @brief 使用互斥锁实现多线程同步
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    pthread_t tids1[THREAD_SIZE]; //线程数组1
    pthread_t tids2[THREAD_SIZE]; //线程数组2
    int ret1;
    int ret2;
    printf("主线程tid:%ld,开始了,count:%d ...\n", pthread_self(), count);
    for (int i = 0; i < THREAD_SIZE; i++)
    {
        ret1 = pthread_create(&tids1[i], nullptr, threadFunction, nullptr); //创建线程tids1[i]
        if (ret1 != 0)
        {
            perror("pthread_create error");
            exit(0);
        }
        ret2 = pthread_create(&tids2[i], nullptr, threadFunction, nullptr); //创建线程tids1[i]
        if (ret2 != 0)
        {
            perror("pthread_create error");
            exit(0);
        }
    }
    printf("主线程tid:%ld,执行了,count:%d ...\n", pthread_self(), count);
    for (int i = 0; i < THREAD_SIZE; i++)
    {
        pthread_join(tids1[i], nullptr);
        pthread_join(tids2[i], nullptr);
    }
    printf("主线程tid:%ld,结束执行了,count:%d ...\n", pthread_self(), count);

    cout << endl;
}

/**
 * @brief 线程回调函数
 *
 * @param para 向线程传递的参数
 * @return void*
 */
void *threadFunction(void *para)
{
    for (int i = 0; i < 100000; i++)
    {
        pthread_mutex_lock(&mutex); //互斥锁加锁
        count++;
        pthread_mutex_unlock(&mutex); //互斥锁解锁
    }
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