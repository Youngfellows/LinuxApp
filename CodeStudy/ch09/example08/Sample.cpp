#include "./include/Sample.h"

void test1()
{
    cout << "test1():: ..." << endl;
    NetUtil::getIP();
    cout << endl;
}

void test2()
{
    cout << "test2():: ..." << endl;
    std::shared_ptr<TCPServer> tcpServer = std::make_shared<TCPServer>();
    bool res = tcpServer->create(); //创建TCP服务端
    if (res)
    {
        res = tcpServer->bindSocket(); //绑定本机网络地址信息
        if (res)
        {
            res = tcpServer->listenSocket(); //监听TCP Socket套接字
            if (res)
            {
                tcpServer->acceptSocket(); //等待客户端来连接服务端
            }
        }
    }

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