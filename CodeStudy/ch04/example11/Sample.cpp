#include "./include/Sample.h"

/**
 * @brief 1. 获取线程的分离状态属性
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    pthread_t tid;                                                //线程ID
    int ret;                                                      //线程创建结果
    ret = pthread_create(&tid, nullptr, threadFunction, nullptr); //创建线程
    if (ret != 0)
    {
        perror("pthread_create error");
        exit(0); //退出进程
    }
    pthread_join(tid, nullptr); //等待子线程结束
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
    printf("子线程ID:%ld\n", tid);
    int ret;                                          //获取线程分离状态属性结果
    int state;                                        //线程分离状态属性
    pthread_attr_t gattr;                             //线程属性结构体
    ret = pthread_getattr_np(pthread_self(), &gattr); //获取当前线程的属性结构体值
    if (ret != 0)
    {
        handle_error_en(ret, "pthread_getattr_np"); //打印错误信息
    }
    printf("线程ID:%ld,的分离状态属性为:\n", tid);
    ret = pthread_attr_getdetachstate(&gattr, &state); //从线程属性结构体中,获取线程分离状态属性
    if (ret)
    {
        handle_error_en(ret, "pthread_attr_getdetachstate");
    }
    //打印线程的当前分离状态属性
    if (state == PTHREAD_CREATE_DETACHED)
    {
        printf("线程的分离状态图属性:%s\n", "PTHREAD_CREATE_DETACHED");
    }
    else if (state == PTHREAD_CREATE_JOINABLE)
    {
        printf("线程的分离状态图属性:%s\n", "PTHREAD_CREATE_JOINABLE");
    }

    return (void *)nullptr;
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