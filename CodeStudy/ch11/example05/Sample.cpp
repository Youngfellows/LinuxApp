#include "./include/Sample.h"

void test1()
{
    cout << "test1():: ..." << endl;
    //多线程管理服务端连接
    TCPServerManager *manager = new TCPServerManager();
    manager->createSocket();
    manager->bindSocket();
    manager->listenSocket();
    manager->acceptSocket();

    //释放内存
    delete manager;
    cout << endl;
}

void test2()
{
    cout << "test2():: ..." << endl;
    //创建5个线程,获取线程ID
    for (int j = 0; j < 5; j++)
    {
        std::thread thread_test([]()
                                {
        for(int i = 0; i < 10; i++)
        {
             int id = syscall(SYS_gettid);
             cout << "test2():: thread_id:" << std::this_thread::get_id() << ",id:" << id << ",i:" << i << endl;
               
        } });
        //等待线程结束
        thread_test.join();
    }

    cout << endl;
}

void test3()
{
    cout << "test3():: ..." << endl;
    thread t([]()
             {
        int id = syscall(SYS_gettid);
        thread::id this_thread_id = this_thread::get_id(); // 获取本线程的id
        cout << "在线程ID:"<< id <<",this_thread_id:" << this_thread_id << "中执行..." << endl; });
    thread::id thread_id = t.get_id();                 // 获取特定线程的id
    thread::id this_thread_id = this_thread::get_id(); // 获取本线程的id

    cout << "thread id = " << thread_id << endl;
    cout << "this thread id = " << this_thread_id << endl;

    t.join();
    cout << endl;
}

void test4()
{
    cout << "test4():: ..." << endl;
    std::thread t1(myTask1);
    std::thread t2(myTask1);
    t1.join();
    t2.join();
    while (true)
    {
        }
    cout << "test4():: main finish ..." << endl;
    cout << endl;
}