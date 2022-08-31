#include "./include/Sample.h"

/**
 * @brief 取消线程时,引发清理函数
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    pthread_t tid;           //线程ID
    int res;                 //线程创建结果
    void *pReturn = nullptr; //线程返回值
    res = pthread_create(&tid, nullptr, threadFunction, nullptr);
    if (res != 0)
    {
        printf("pthread_create failed: %s\n", strerror(res));
        exit(1); //结束进程
    }
    sleep(1);                        //等待一会儿,让子线程执行
    pthread_cancel(tid);             //发送取消线程的请求
    pthread_join(tid, &pReturn);     //等待子线程结束
    if (pReturn == PTHREAD_CANCELED) //判断线程是否取消成功
    {
        printf("取消线程成功\n");
    }
    else
    {
        printf("取消线程错误\n");
    }
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
    int i = 1;
    pthread_t tid = pthread_self(); //获取线程ID
    printf("子线程开始执行,线程ID:%ld\n", tid);
    pthread_cleanup_push(myCleanFunction, &i); //把清理函数压栈
    while (true)
    {
        i++;
        printf("i=%d\n", i);
    }
    printf("这句不会调用"); //这句不会调用
    pthread_cleanup_pop(0); //仅仅是为了成对调用
    return (void *)0;
}

/**
 * @brief 线程清理函数
 *
 * @param arg
 */
void myCleanFunction(void *arg)
{
    printf("执行清理函数:%d\n", *((int *)arg));
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