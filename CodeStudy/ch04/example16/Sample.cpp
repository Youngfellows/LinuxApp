#include "./include/Sample.h"

/**
 * @brief 1. 线程主动结束,并接收线程的返回值
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    pthread_t threads[PTHREAD_NUM];                                       //线程数组
    int ret;                                                              //线程创建结果
    int *pReturn1;                                                        //线程1的返回结果
    int *pReturn2;                                                        //线程2的返回结果
    ret = pthread_create(&threads[0], nullptr, threadFunction1, nullptr); //创建线程1
    if (ret != 0)
    {
        handle_error_en(ret, "pthread_create thread1 failed");
    }
    ret = pthread_create(&threads[1], nullptr, threadFunction2, nullptr); //创建线程2
    if (ret != 0)
    {
        handle_error_en(ret, "pthread_create thread2 failed");
    }

    //等待线程1结束,并获取线程的返回值
    if (threads[0] != 0)
    {
        pthread_join(threads[0], (void **)&pReturn1);
        printf("线程1的返回值是:%d\n", *pReturn1);
    }

    //等待线程1结束,并获取线程的返回值
    if (threads[1] != 0)
    {
        pthread_join(threads[1], (void **)&pReturn2);
        printf("线程2的返回值是:%d\n", *pReturn2);
    }
    cout << endl;
}

/**
 * @brief 线程回调函数
 *
 * @param para
 * @return void*
 */
void *threadFunction1(void *para)
{
    static int count = 1024;        //静态变量，开辟在堆空间的
    pthread_exit((void *)(&count)); //通过pthread_exit()结束线程
}

/**
 * @brief 线程回调函数
 *
 * @param para
 * @return void*
 */
void *threadFunction2(void *para)
{
    static int number = 2048; //静态变量，开辟在堆空间的
    return (void *)(&number); //线程函数返回
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