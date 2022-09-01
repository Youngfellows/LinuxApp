#include "./include/Sample.h"

//定义全局变量
std::atomic<bool> ready(false);

/**
 * @brief 1. yield()函数让出CPU时间
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    std::thread threads[THREAD_NUMBER]; //定义10个线程对象
    cout << THREAD_NUMBER << "个线程,每个线程都累加到一百万" << endl;
    for (int i = 0; i < THREAD_NUMBER; i++)
    {
        threads[i] = std::thread(threadFunction, i); //启动线程,把i作为参数传递给线程,用于标记线程的序号
    }
    ready = true; //重置全局变量
    for (auto &th : threads)
    {
        th.join(); //等待10个线程结束
    }
    cout << endl;
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

/**
 * @brief 线程回调函数
 *
 */
void threadFunction(int id)
{
    //一直等待,直到main线程中重置全局变量ready=true
    while (!ready)
    {
        std::this_thread::yield(); //让出自己的CPU时间片段
    }
    //开始累计到1百万
    for (int i = 0; i < 1000000; i++)
    {
    }
    //累加完毕,打印本线程的序号,最终结果就是排名
    cout << id << ",";
}