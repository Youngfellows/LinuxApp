#ifndef HANDLE_THREAD_H
#define HANDLE_THREAD_H

#include "../Global.h"
#include "./TCPServerManager.h"

//先声明类,后面再定义
class TCPServerManager;

/**
 * @brief 处理客户端连接的线程
 *
 */
class HandleThread
{
private:
    TCPServerManager *manager = nullptr; //服务端对象

public:
    HandleThread(TCPServerManager *manager);
    ~HandleThread();
    void start();   //启动一个线程
    void process(); //线程回调函数
};
#endif