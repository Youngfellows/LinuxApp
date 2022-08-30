#include "./include/Sample.h"

/**
 * @brief 取消线程
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    pthread_t tid;                                                //线程ID
    int ret;                                                      //线程创建结果
    int *pReturn;                                                 //线程返回值
    ret = pthread_create(&tid, nullptr, threadFunction, nullptr); //创建线程
    if (ret != 0)
    {
        handle_error_en(ret, "pthread_create error");
    }
    sleep(2);                               // CPU休眠2秒,让子线程运行
    pthread_cancel(tid);                    //发送取消线程的请求
    pthread_join(tid, (void **)(&pReturn)); //等待子线程结束,并接收子线程的返回值
    // printf("pReturn=%p,*pReturn=%d\n", pReturn, *pReturn);
    printf("pReturn=%p\n", pReturn);
    printf("PTHREAD_CANCELED=%p\n", PTHREAD_CANCELED);
    //判断是否取消线程成功
    if (pReturn == PTHREAD_CANCELED)
    {
        printf("子线程已经退出了,子线程ID:%ld\n", tid);
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
    pthread_t tid = pthread_self(); //获取线程ID
    printf("子线程开始了,线程ID:%ld\n", tid);
    int i = 1;
    while (true)
    {
        i++;
        pthread_testcancel(); //让系统测试取消请求
    }
    return (void *)0;
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