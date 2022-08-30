#include "./include/Sample.h"

/**
 * @brief 1. 线程被动结束
 * @brief 2. 向线程发送请求结束信号
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    pthread_t tid;                                                //线程ID
    int ret;                                                      //线程创建结果
    int *pReturn;                                                 //
    ret = pthread_create(&tid, nullptr, threadFunction, nullptr); //创建子线程
    if (ret != 0)
    {
        handle_error_en(ret, "pthread_create error");
    }
    sleep(5);                               //让出CPU 5秒,让子线程执行
    pthread_kill(tid, SIGQUIT);             // 5秒结束后,开始向子线程发送SIGQUITE信号,通知其结束
    pthread_join(tid, (void **)(&pReturn)); //等待子线程结束并接受线程的返回结果
    printf("主线程Thread ID:%ld,子线程的返回结果:%d\n", pthread_self(), *pReturn);
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
    signal(SIGQUIT, onSignalTerm);  //注册信号处理函数
    pthread_t tid = pthread_self(); //获取线程ID
    int number = 50;
    while (true)
    {
        printf("%d,子线程ID:%ld\n", number, tid);
        sleep(1); //阻塞1秒
        number--;
    }
    static int count = 2049;
    return (void *)(&count); //线程函数返回
}

/**
 * @brief 信号处理函数
 *
 * @param sig
 */
void onSignalTerm(int sig)
{
    printf("子线程将要退出,线程ID:%ld\n", pthread_self());
    static int count = 2010053304;
    pthread_exit((void *)(&count));
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