#include "./include/Sample.h"

//进程数据
int x = 0;
int y = 0;

/**
 * @brief 线程共享进程数据
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    pthread_t tid1; //线程1 ID
    pthread_t tid2; //线程1 ID
    int ret1;
    int ret2;
    //创建线程1
    ret1 = pthread_create(&tid1, nullptr, threadFunction1, nullptr);
    if (ret1 != 0)
    {
        perror("pthread_create error");
        exit(0); //结束进程
    }
    //创建线程2
    ret2 = pthread_create(&tid2, nullptr, threadFunction2, nullptr);
    if (ret2 != 0)
    {
        perror("pthread_create error");
        exit(0); //结束进程
    }
    //等待子线程执行完成
    pthread_join(tid1, nullptr);
    pthread_join(tid2, nullptr);
    printf("主线程Thread ID:%ld,x:%d,y:%d\n", pthread_self(), x, y);
    cout << endl;
}

void *threadFunction1(void *para) //线程1回调函数
{
    pthread_t tid = pthread_self(); //获取线程ID
    printf("子线程1执行,Start,Thread ID:%ld\n", tid);
    y = 7;
    sleep(1); //阻塞1线程1秒
    printf("子线程1执行,End,Thread ID:%ld\n", tid);
    x = x + y;
    pthread_exit(0); //结束线程
}

void *threadFunction2(void *para) //线程2回调函数
{
    pthread_t tid = pthread_self(); //获取线程ID
    printf("子线程2执行,Start,Thread ID:%ld\n", tid);
    x = 4;
    sleep(1); //阻塞2线程1秒
    printf("子线程2执行,End,Thread ID:%ld\n", tid);
    y = 8 + y;
    pthread_exit(0); //结束线程
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