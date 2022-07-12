#include "../../include/server/HandleThread.h"

HandleThread::HandleThread()
{
    cout << "HandleThread()构造函数" << endl;
    // this->server = server;
}

HandleThread::~HandleThread()
{
    cout << "~HandleThread()析构函数" << endl;
}

void HandleThread::start(int connfd, struct sockaddr_in client)
{
    cout << "HandleThread::start():: ..." << endl;
    // string city = "广东省深圳市南山区";
    // //创建一个线程
    // std::thread *thread_test = new std::thread(myThread5, std::ref(city));
    // cout << "test7():: main,1,city=" << city << endl;
    // //等待线程结束
    // thread_test->join();

    //创建线程
    std::shared_ptr<std::thread> handle = std::make_shared<thread>(process, std::ref(connfd), std::ref(client));
    //等待线程结束
    handle->join();
}

/**
 * @brief 线程回调函数,传递参数给线程回调函数
 *
 * @param connfd 客户端socket连接描述符
 * @param client 客户端地址信息
 */
void HandleThread::process(int connfd, struct sockaddr_in remote_addr)
{
    cout << "HandleThread::process():: " << endl;
    char *remote = inet_ntoa(remote_addr.sin_addr);
    cout << "HandleThread::process():: remote ip:" << remote << ",connfd:" << connfd << endl;
    // server->receive(connfd, client);
    receive(connfd, remote_addr);
}

/**
 * @brief 接收客户端数据
 * @brief 开启多线程处理每一个远程客户端连接,否则可能出现一直阻塞的现象,新的客户端连接过来了,可以关闭掉旧的客户端
 *
 * @param connfd 客户端套接字描述符
 * @param client 客户端地址
 * @return true
 * @return false
 */
bool HandleThread::receive(int connfd, struct sockaddr_in remote_addr)
{
    char *remote = inet_ntoa(remote_addr.sin_addr);
    cout << "HandleThread::receive():: remote ip:" << remote << ",connfd:" << connfd << endl;
    int receiveNum = 0;                //接收数据大小
    char receiveBuffer[MAX_DATA_SIZE]; //接收数据缓冲区

    receiveNum = recv(connfd, receiveBuffer, MAX_DATA_SIZE, 0);
    if (receiveNum == -1)
    {
        //接收数据异常,关闭连接
        cout << "HandleThread::receive():: 1,接收数据异常,remote ip:" << remote << ",connfd:" << connfd << endl;
        // this->remove(connfd);
        // this->closeRemote(connfd);
        return false;
    }
    else
    {
        cout << "HandleThread::receive():: 1,接收到,receiveNum:" << receiveNum << ",receiveBuffer:" << receiveBuffer << endl;
    }

    //循环接收数据
    while ((receiveNum = recv(connfd, receiveBuffer, MAX_DATA_SIZE, 0)))
    {
        cout << "HandleThread::receive():: 2,接收到,receiveNum:" << receiveNum << ",receiveBuffer:" << receiveBuffer << endl;
    }
    //接收数据异常,关闭连接
    cout << "HandleThread::receive():: 2,接收数据异常,remote ip:" << remote << ",connfd:" << connfd << endl;
    // this->remove(connfd);
    // this->closeRemote(connfd);
    return true;
}