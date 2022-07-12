#ifndef SERVER_SOCKET_MANAGER_H
#define SERVER_SOCKET_MANAGER_H

#include "../Global.h"
#include "./HandleThread.h"

//先声明类,后面再定义
class HandleThread;

/**
 * @brief 服务端套接字多线程管理者
 *
 */
class TCPServerManager
{
private:
public:
    TCPServerManager();
    ~TCPServerManager();
    void createSocket();  //创建套接字
    void bindSocket();    //绑定端口
    void listenSocket();  //监听套接字
    void acceptSocket();  //接收客户端连接
    void receiveRemote(); //接收客户端消息
    void sendRemote();    //发送消息给客户端
    void closeRemote();   //关闭客户端
    void closeSelf();     //关闭服务端
};
#endif