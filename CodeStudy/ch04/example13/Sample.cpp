#include "./include/Sample.h"

/**
 * @brief 获取线程默认栈尺寸大小和最小尺寸
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
        handle_error_en(ret, "pthread_create failed");
    }
    pthread_join(tid, nullptr); //等待子线程结束
    cout << endl;
}

void *threadFunction(void *para) //线程回调函数
{
    pthread_t tid = pthread_self();        //获取线程ID
    pthread_attr_t gattr;                  //线程属性结构体
    size_t stackSize;                      //线程栈尺寸大小
    int res;                               //获取结果状态
    res = pthread_getattr_np(tid, &gattr); //获取线程属性结构体
    if (res != 0)
    {
        handle_error_en(res, "pthread_getattr_np failed");
    }
    res = pthread_attr_getstacksize(&gattr, &stackSize); //获取线程默认栈尺寸大小
    if (res != 0)
    {
        handle_error_en(res, "pthread_attr_getstacksize failed");
    }
    printf("线程默认栈尺寸大小%lu个字节,最小尺寸%u个字节\n", stackSize, PTHREAD_STACK_MIN);
    pthread_attr_destroy(&gattr); //销毁线程属性
    pthread_exit(0);              //结束线程
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