#include "../include/interface/MyTask.h"

//互斥变量
std::mutex g_display_mutex;

//在文件外实现线程回调函数
void myTask1()
{
    std::thread::id this_id = std::this_thread::get_id();
    unsigned int t = *(unsigned int *)&this_id; // threadid 转成 unsigned int
    unsigned int threadid = t;
    g_display_mutex.lock();
    std::cout << "myTask1():: this_id:" << this_id << " ,sleeping...\n";
    std::cout << "myTask1():: threadid:" << threadid << endl;
    g_display_mutex.unlock();
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void myTask2()
{
}