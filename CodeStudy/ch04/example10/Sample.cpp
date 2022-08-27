#include "./include/Sample.h"

/**
 * @brief 1. 创建一个可分离线程,主线程先退出
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    pthread_t tid;                  //线程ID
    pthread_attr_t attr;            //线程结构体属性
    int res;                        //执行结果
    res = pthread_attr_init(&attr); //初始化线程结构体属性
    if (res != 0)
    {
        perror("pthread_attr_init error");
        cout << "pthread_attr_init failed:" << res << endl;
    }
    //设置线程属性为分离状态
    res = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if (res)
    {
        perror("pthread_attr_setdetachstate error");
        cout << "pthread_attr_setdetachstate failed:" << res << endl;
    }
    //创建一个可分离线程
    res = pthread_create(&tid, &attr, threadFunction, nullptr);
    if (res)
    {
        perror("pthread_create error");
        cout << "pthread_create failed:" << res << endl;
    }
    printf("主线程:%ld,将要退出...\n", pthread_self());
    pthread_exit(nullptr); //主线程退出,但进程并没有结束,下面的语句不回执行
    cout << "主线程已经退出了,这一句不回执行 ..." << endl;

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
    pthread_t tid;        //线程ID
    tid = pthread_self(); //获取线程ID
    printf("子线程ID:%ld,开始执行了 ...\n", tid);
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

    sleep(3); //子线程阻塞3秒
    printf("子线程ID:%ld,结束了 ...\n", tid);
    pthread_exit(0); //结束子线程
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