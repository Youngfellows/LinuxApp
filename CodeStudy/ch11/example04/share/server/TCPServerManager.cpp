#include "../../include/server/TCPServerManager.h"

TCPServerManager::TCPServerManager()
{
    cout << "TCPServerManager()构造函数" << endl;
}

TCPServerManager::~TCPServerManager()
{
    cout << "~TCPServerManager()析构函数" << endl;
}

void TCPServerManager::createSocket() //创建套接字
{
    cout << "TCPServerManager::createSocket():: ..." << endl;
}

void TCPServerManager::bindSocket() //绑定端口
{
    cout << "TCPServerManager::bindSocket():: ..." << endl;
}

void TCPServerManager::listenSocket() //监听套接字
{
    cout << "TCPServerManager::listenSocket():: ..." << endl;
}

/**
 * @brief 接收客户端连接
 * @brief 开启多线程处理
 *
 */
void TCPServerManager::acceptSocket()
{
    cout << "TCPServerManager::acceptSocket():: ..." << endl;
    for (int i = 0; i < 10; i++)
    {
        //创建一个线程
        // HandleThread *handlerThread = new HandleThread(this);
        // std::thread *processThread = new std::thread(&&HandleThread::process, handlerThread);
        // processThread->join();

        HandleThread *handlerThread = new HandleThread(this);
        handlerThread->start(); //启动多线程
    }
}

void TCPServerManager::receiveRemote() //接收客户端消息
{
    cout << "TCPServerManager::receiveRemote():: ..." << endl;
}

void TCPServerManager::sendRemote() //发送消息给客户端
{
    cout << "TCPServerManager::sendRemote():: ..." << endl;
}

void TCPServerManager::closeRemote() //关闭客户端
{
    cout << "TCPServerManager::closeRemote():: ..." << endl;
}

void TCPServerManager::closeSelf() //关闭服务端
{
    cout << "TCPServerManager::closeSelf():: ..." << endl;
}