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

/**
 * @brief 启动一个线程
 *
 */
void HandleThread::start()
{
    cout << "HandleThread::start():: 启动一个线程执行 ..." << endl;
    std::thread *processThread = new std::thread(&HandleThread::process, this);
    // processThread->join(); //等待线程结束
    processThread->detach();
}

/**
 * @brief 线程回调函数
 *
 */
void HandleThread::process()
{
    for (int i = 0; i < 5; i++)
    {
        cout << "HandleThread::process():: " << i << " ,start ..." << endl;
        std::thread::id this_id = std::this_thread::get_id();
        unsigned int t = *(unsigned int *)&this_id; // threadid 转成 unsigned int
        unsigned int threadid = t;
        int id = syscall(SYS_gettid);
        g_display_mutex.lock();
        std::cout << "HandleThread::process():: this_id:" << this_id << " ,sleeping...\n";
        std::cout << "HandleThread::process():: threadid:" << threadid << endl;
        std::cout << "HandleThread::process():: id:" << id << endl;
        g_display_mutex.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        this->manager->sendRemote(); //调用发送数据
        cout << "HandleThread::process():: " << i << " ,end ..." << endl;
    }
}
