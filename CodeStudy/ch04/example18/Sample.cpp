#include "./include/Sample.h"

/**
 * @brief 判断线程是否已经结束
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    pthread_t tid;                                                //线程ID
    int ret;                                                      //线程创建结果
    int *pReturn;                                                 //线程返回结果
    ret = pthread_create(&tid, nullptr, threadFunction, nullptr); //创建线程
    if (ret != 0)
    {
        handle_error_en(ret, "pthread_create failed");
    }
    sleep(5);                              //主线程休眠5秒,让子线程执行
    int killResult = pthread_kill(tid, 0); //发送信号0,探测线程是否存活
    if (killResult == ESRCH)
    {
        printf("指定线程ID为%ld的线程不存在或者线程已经退出了\n", tid);
    }
    else if (killResult == EINVAL)
    {
        printf("信号不合法\n");
    }
    else
    {
        printf("指定线程ID为%ld的线程存活\n", tid);
    }

    pthread_join(tid, (void **)(&pReturn)); //等待子线程结束,并接收线程的返回值
    printf("主线程%ld,接收到子线程的返回结果:%d\n", pthread_self(), *pReturn);

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
    pthread_t tid = pthread_self(); //获取线程ID
    int number = 50;
    while (true)
    {
        if (number < 48)
        {
            break;
        }
        printf("%d,子线程ID:%ld\n", number, tid);
        sleep(1); //阻塞1秒
        number--;
    }
    static int count = 2049;
    return (void *)(&count); //线程函数返回
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