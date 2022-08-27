#include "./include/Sample.h"

/**
 * @brief 将可连接状态线程转化为可分离状态线程
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    printf("主线程,执行了,线程ID:%ld\n", pthread_self());
    pthread_t tid;                                                //线程ID
    int ret;                                                      //线程创建结果
    ret = pthread_create(&tid, nullptr, threadFunction, nullptr); //创建线程
    if (ret != 0)
    {
        handle_error_en(ret, "pthread_create error"); //打印错误信息
    }
    pthread_exit(nullptr); //主线程退出,但是进程并不是马上结束
    printf("主线程已经退出了,线程ID:%ld,这句将不会执行...\n", pthread_self());
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
    pthread_t tid;                         //获取线程ID
    pthread_attr_t gattr;                  //线程属性结构体
    int state;                             //线程分离状态属性
    int ret;                               //执行结果
    tid = pthread_self();                  //获取线程ID
    ret = pthread_getattr_np(tid, &gattr); //获取线程属性结构体值
    if (ret != 0)
    {
        handle_error_en(ret, "pthread_getattr_np failed");
    }

    //从线程属性结构体中获取线程的分离状态属性
    ret = pthread_attr_getdetachstate(&gattr, &state);
    if (ret != 0)
    {
        handle_error_en(ret, "pthread_attr_getdetachstate failed");
    }
    if (state == PTHREAD_CREATE_DETACHED)
    {
        printf("线程的分离状态属性:%s\n", "PTHREAD_CREATE_DETACHED");
    }
    else if (state == PTHREAD_CREATE_JOINABLE)
    {
        printf("线程的分离状态属性:%s\n", "PTHREAD_CREATE_JOINABLE");
    }
    else
    {
        printf("未知的线程分离状态属性\n");
    }

    pthread_detach(tid); //转化为分离状态属性线程
    sleep(3);            //线程阻塞3秒
    printf("转化后\n");

    //从线程属性结构体中获取线程的分离状态属性
    ret = pthread_getattr_np(tid, &gattr); //获取线程属性结构体值
    if (ret != 0)
    {
        handle_error_en(ret, "pthread_getattr_np failed");
    }

    ret = pthread_attr_getdetachstate(&gattr, &state);
    if (ret != 0)
    {
        handle_error_en(ret, "pthread_attr_getdetachstate failed");
    }
    if (state == PTHREAD_CREATE_DETACHED)
    {
        printf("线程的分离状态属性:%s\n", "PTHREAD_CREATE_DETACHED");
    }
    else if (state == PTHREAD_CREATE_JOINABLE)
    {
        printf("线程的分离状态属性:%s\n", "PTHREAD_CREATE_JOINABLE");
    }
    else
    {
        printf("未知的线程分离状态属性\n");
    }

    pthread_attr_destroy(&gattr); //销毁属性
    pthread_exit(nullptr);        //子线程结束退出
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