#include "./include/Sample.h"

//全局变量
volatile int mCounter(0); //计数器
std::mutex mMutex;        //用于保护计数器的互斥锁

/**
 * @brief C++ 11使用互斥锁进行多线程同步处理
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    std::thread threads[THREAD_NUMBER]; //线程列表
    //启动10个线程
    for (int i = 0; i < THREAD_NUMBER; i++)
    {
        threads[i] = std::thread(threadFunction); //启动10个线程
    }
    //等待10个线程结束
    for (auto &th : threads)
    {
        th.join(); //等待10个线程结束
    }
    cout << "Sucessfull,mCounter:" << mCounter << endl;
    cout << endl;
}

/**
 * @brief 线程回调函数
 *
 */
void threadFunction()
{
    for (int i = 0; i < 200000; i++)
    {
        if (mMutex.try_lock()) //互斥锁上锁
        {
            mCounter++;      //共享数据累加
            mMutex.unlock(); //互斥锁释放锁
        }
        else
        {
            cout << "尝试上锁失败 ... " << endl;
        }
    }
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