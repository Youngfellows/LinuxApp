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