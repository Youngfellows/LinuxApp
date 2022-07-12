#ifndef HANDLE_THREAD_H
#define HANDLE_THREAD_H

#include "../interface/IHandleThread.h"

/**
 * @brief 处理客户端请求数据线程类
 *
 */
class HandleThread : public IHandleThread
{
private:
    // std::shared_ptr<ITcpServer> server = nullptr; //服务端对象

public:
    HandleThread();
    ~HandleThread();
    virtual void start(int connfd, struct sockaddr_in client) override; //实现start函数
private:
    static void process(int connfd, struct sockaddr_in client); //线程回调函数
    static bool receive(int connfd, struct sockaddr_in client);
};
#endif