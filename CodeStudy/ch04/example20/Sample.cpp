#include "./include/Sample.h"

/**
 * @brief 线程主动结束时,调用清理函数
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    pthread_t tid1;                                                 //线程ID
    pthread_t tid2;                                                 //线程ID
    int *pReturn1;                                                  //线程1的返回结果
    int *pReturn2;                                                  //线程2的返回结果
    int res;                                                        //线程创建结果
    res = pthread_create(&tid1, nullptr, threadFunction1, nullptr); //创建线程1
    if (res)                                                        // res != 0
    {
        printf("pthread_create failed: %s\n", strerror(res));
        exit(1); //结束进程
    }
    pthread_join(tid1, (void **)&pReturn1); //等待线程1结束
    printf("主线程Thread ID:%ld,子线程1的Thread ID:%ld,返回结果是:%d\n", pthread_self(), tid1, *pReturn1);

    res = pthread_create(&tid2, nullptr, threadFunction2, nullptr); //创建线程2
    if (res)
    {
        printf("pthread_create failed: %s\n", strerror(res));
        exit(1);
    }
    pthread_join(tid2, (void **)&pReturn2); //等待线程2结束
    printf("主线程Thread ID:%ld,子线程2的Thread ID:%ld,返回结果是:%d\n", pthread_self(), tid2, *pReturn2);
    printf("主线程Thread ID:%ld,结束运行了\n", pthread_self());
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
    pthread_t tid = pthread_self(); //获取线程ID
    printf("子线程1开始运行了,Thread ID:%ld\n", tid);
    static int count = 1024;
    int m = 111;
    pthread_cleanup_push(myCleanFunction, &m); //把清理函数压栈
    pthread_exit((void *)&count);              //退出线程
    pthread_cleanup_pop(0);                    //把清理函数出栈,这句不会执行,单必须有,否则编译不过
}

/**
 * @brief 线程回调函数
 *
 * @param para
 * @return void*
 */
void *threadFunction2(void *para)
{
    pthread_t tid = pthread_self(); //获取线程ID
    printf("子线程2开始运行了,Thread ID:%ld\n", tid);
    static int count = 2048;
    int m = 222;
    pthread_cleanup_push(myCleanFunction, &m); //把清理函数压栈
    // pthread_exit((void *)(&count));            //退出线程
    return (void *)&count;
    pthread_cleanup_pop(0); //把清理函数出栈,这句不会执行,单必须有,否则编译不过
}

/**
 * @brief 线程清理函数
 *
 * @param arg
 */
void myCleanFunction(void *arg)
{
    pthread_t tid = pthread_self(); //获取线程ID
    printf("执行线程Thread ID:%ld,的清理函数,arg:%d\n", tid, *((int *)arg));
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