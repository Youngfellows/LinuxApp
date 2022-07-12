#include "../../include/server/HandleThread.h"

HandleThread::HandleThread(TCPServerManager *manager)
{
    cout << "HandleThread()构造函数" << endl;
    this->manager = manager;
}

HandleThread::~HandleThread()
{
    cout << "~HandleThread()析构函数" << endl;
}

// //创建线程,通过指针获取对象
// std::thread *thread_test1 = new std::thread(&MyThread6::myTask, mythread);
// std::thread *thread_test2 = new std::thread(&MyThread6::myTask, mythread);

// //等待线程结束
// thread_test1->join();
// thread_test2->join();

/**
 * @brief 启动一个线程
 *
 */
void HandleThread::start()
{
    cout << "HandleThread::start():: 启动一个线程" << endl;
}

void HandleThread::process()
{
    cout << "HandleThread::process()::" << endl;
}
