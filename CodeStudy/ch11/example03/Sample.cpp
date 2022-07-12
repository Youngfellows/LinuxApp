#include "./include/Sample.h"

void test1()
{
    cout << "test1():: ..." << endl;
    // TCP客户端
    std::shared_ptr<ITcpClient> client = std::make_shared<NetTcpClient>();
    bool res = client->createSocket(); //创建socket套接字
    cout << "test1():: create:: res:" << res << endl;
    if (!res)
    {
        return;
    }

    res = client->connectServer(); //与服务端连接
    cout << "test1():: connect:: res:" << res << endl;
    if (!res)
    {
        return;
    }

    //首先发送一个消息给服务端
    cout << "客户端输入:";
    
    char sendBuffer[MAX_DATA_SIZE]; //发送数据缓冲区
    std::string message;
    std::cin >> message;
    strcpy(sendBuffer, message.c_str());
    res = client->sendToRemote(sendBuffer); //输入消息并发送给服务端
    cout << "test1():: client send:: res:" << res << endl;
    if (!res)
    {
        return;
    }

    client->receive(); //接收服务端数据

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