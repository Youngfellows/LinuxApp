#include "./include/Sample.h"

/**
 * @brief pthread_cleanup_pop调用清理函数
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    pthread_t tid;                                                //线程ID
    int res;                                                      //线程创建结果
    int *pReturn;                                                 //子线程的返回结果
    res = pthread_create(&tid, nullptr, threadFunction, nullptr); //创建线程
    if (res != 0)
    {
        printf("pthread_create failed: %s\n", strerror(res));
        exit(1);
    }
    pthread_join(tid, (void **)&pReturn); //等待子线程结束
    printf("主线程结束了,Thread ID:%ld,子线程的返回值:%d\n", pthread_self(), *pReturn);
    cout << endl;
}

/**
 * @brief 线程回调函数
 *
 * @param para
 * @return void*
 */
void *threadFunction(void *para)
{
    int m = 1024;
    int n = 2048;
    static int count = 3333;
    pthread_t tid = pthread_self(); //获取线程ID
    printf("子线程执行了,Thread ID:%ld\n", tid);
    pthread_cleanup_push(myCleanFunction, &m); //把清理函数压栈
    pthread_cleanup_push(myCleanFunction, &n); //把清理函数压栈
    pthread_cleanup_pop(1);                    //出栈清理函数,并执行
    pthread_exit((void *)&count);              //退出线程
    pthread_cleanup_pop(0);                    //不会执行,仅仅是为了成对
}

/**
 * @brief 线程清理函数
 *
 * @param arg
 */
void myCleanFunction(void *arg)
{
    printf("执行线程清理函数:%d\n", *((int *)arg));
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