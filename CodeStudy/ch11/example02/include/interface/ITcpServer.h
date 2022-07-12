#ifndef ITCP_SERVER_H
#define ITCP_SERVER_H

#include "../Global.h"
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

/**
 * @brief 抽象TCP服务端接口
 *
 */
class ITcpServer
{
public:
    virtual ~ITcpServer() = default;
    virtual bool createSocket() = 0;                                 //创建socket
    virtual void setReusePort() = 0;                                 //设置端口可重用
    virtual bool bindSocket() = 0;                                   //绑定到IP地址
    virtual bool listenSocket() = 0;                                 //简单socket套接字
    virtual void acceptRemote() = 0;                                 //接收客户端连接
    virtual bool receive(int connfd, struct sockaddr_in client) = 0; //接收到客户端数据
    virtual bool sendToRemote() = 0;                                 //发送数据给客户端
    virtual void closeRemote(int remotefd) = 0;                      //关闭客户端远程连接
    virtual void closeServer() = 0;                                  //关闭服务端连接
    virtual void add(int connfd, char *ip) = 0;                      //添加到容器
    virtual void remove(int connfd) = 0;                             //从容器移除
    virtual bool isConnect() = 0;                                    //是否连接上
};

#endif