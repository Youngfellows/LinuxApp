#include "./include/Sample.h"

void test1()
{
    cout << "test1():: ..." << endl;
    //启动TCP 服务端
    std::shared_ptr<ITcpServer> server = std::make_shared<NetTcpServer>();
    bool res = server->createSocket();
    cout << "creat:: res:" << res << endl;
    if (!res)
    {
        return;
    }
    server->setReusePort();
    res = server->bindSocket();
    cout << "bind:: res:" << res << endl;
    if (!res)
    {
        return;
    }
    server->acceptRemote();

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