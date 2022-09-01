#include "./include/Sample.h"

//主线程的线程标识符
std::thread::id mainThreadId = std::this_thread::get_id(); //获取主线程ID

/**
 * @brief 1. 获取线程ID
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    std::thread::id tid = std::this_thread::get_id(); //获取线程ID
    cout << "主线程Thread ID:" << tid << endl;
    isMainThread();                     //主函数掉用普通函数
    std::thread myThread(isMainThread); //创建一个线程对象
    myThread.join();                    //等待子线程结束
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
 * @brief 打印是否是主线程
 *
 */
void isMainThread()
{
    std::thread::id tid = std::this_thread::get_id(); //获取线程ID
    //判断线程ID是否和主线程相同
    if (mainThreadId == tid)
    {
        cout << "这个线程是主线程,Thread ID:" << tid << endl;
    }
    else
    {
        cout << "这个线程不是主线程,Thread ID:" << tid << endl;
    }
}