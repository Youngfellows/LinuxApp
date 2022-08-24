#include "./include/Sample.h"

/**
 * @brief 主线程通过pthread_join()函数等待子线程结束
 * @brief 子线程一创建就执行回调函数
 */
void test1()
{
    cout << "test1():: ..." << endl;
    const char *msg1 = "明天有台风,请大家下班关好门窗 ...\n";
    const char *msg2 = "如果明天风大雨急,大家不要来上班了 ...\n";
    pthread_t tid1;                                                      //子线程id
    pthread_t tid2;                                                      //子线程id
    int ret1;                                                            //创建线程结果
    int ret2;                                                            //创建线程结果
    ret1 = pthread_create(&tid1, nullptr, threadFunction, (void *)msg1); //创建线程1
    if (ret1 != 0)
    {
        perror("pthread_create error");
        exit(0);
    }
    ret2 = pthread_create(&tid2, nullptr, threadFunction, (void *)msg2); //创建线程2
    if (ret2 != 0)
    {
        perror("pthread_create error");
        exit(0);
    }
    printf("主线程tid:%ld,开始执行了 ...\n", pthread_self());
    pthread_join(tid1, NULL); //等待子线程1结束
    pthread_join(tid2, NULL); //等待子线程2结束
    printf("主线程tid:%ld,结束执行了 ...\n", pthread_self());
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
    char *message = nullptr;
    message = (char *)para;
    pthread_t tid;        //线程id
    tid = pthread_self(); //获取线程id
    printf("子线程tid:%ld,message:%s\n", tid, message);
    sleep(2); //子线程休眠2秒
    printf("子线程tid:%ld,结束运行了 ...\n", tid);
    return nullptr;
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