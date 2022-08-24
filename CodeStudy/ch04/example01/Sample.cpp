#include "./include/Sample.h"

/**
 * @brief 创建线程并输出线程ID
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    pthread_t threadId;                                          //线程ID
    int ret;                                                     //创建结果
    ret = pthread_create(&threadId, NULL, threadFunction, NULL); //创建一个线程
    if (ret != 0)
    {
        perror("pthread_create error");
        exit(1);
    }
    printf("主线程tid:%ld,开始执行 ...\n", pthread_self());
    sleep(1); //主线程休眠一下,让执行有时间执行
    printf("主线程tid:%ld,结束执行 ...\n", pthread_self());
    cout << endl;
}

/**
 * @brief 线程回调函数
 *
 * @param para 向线程传递的参数
 * @return void* 返回值
 */
void *threadFunction(void *para)
{
    pthread_t tid;        //子线程id
    tid = pthread_self(); //获取线程id
    printf("threadFunction():: 子线程tid:%ld,运行 ...\n", tid);
    return (void *)0;
}

/**
 * @brief 线程回调函数
 *
 * @param para
 * @return void*
 */
void *threadFunction2(void *para)
{
    pthread_t tid;        //子线程id
    tid = pthread_self(); //获取线程id
    char *message = nullptr;
    message = (char *)para;
    printf("threadFunction2():: 子线程tid:%ld,运行 ...\n", tid);
    printf("%s\n", message);
    sleep(3); //子线程休眠3秒
    printf("threadFunction2():: 子线程tid:%ld,结束运行 ...\n", tid);
    return (void *)nullptr;
}

/**
 * @brief 主线程退出,进程并没用结束
 *
 */
void test2()
{
    cout << "test2():: ..." << endl;
    const char *message = "今天是星期三,心情好好哦 ...";
    pthread_t tid; //线程id
    int ret;
    ret = pthread_create(&tid, NULL, threadFunction2, (void *)message); //创建线程
    if (ret != 0)
    {
        perror("pthread_create error");
        exit(0);
    }
    printf("主线程tid:%ld,开始了 ...\n", pthread_self());
    pthread_exit(0); //主线程退出,进程并没用结束
    printf("主线程tid:%ld,退出了 ...\n", pthread_self());
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