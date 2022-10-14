#include "./include/Sample.h"

/**
 * @brief TCP客户端
 * @brief 测试: help
 * @brief 测试: exit
 * @brief 测试: ls
 * @brief 测试: get ./file/f1.txt
 * @brief 测试: put ./file/f2.txt
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    std::shared_ptr<ITCPClient> tcpClient = std::make_shared<TCPClient>();
    tcpClient->processMenu();       //显示帮助菜单
    bool res = tcpClient->create(); //创建Socket连接
    if (res)
    {
        res = tcpClient->connectSocket(nullptr); //客户端连接Socket服务端
        if (res)
        {
            tcpClient->inputAndSend(); //输入并连接客户端
        }
    }
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