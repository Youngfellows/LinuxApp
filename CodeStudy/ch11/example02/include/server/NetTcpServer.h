#ifndef NET_TCP_SERVER_H
#define NET_TCP_SERVER_H

#include "../Global.h"
#include "../interface/ITcpServer.h"
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

/**
 * @brief TCP服务端
 * @brief 只支持单客户端,如果有多余一个客户端连接过来,关闭掉上一个连接
 *
 */
class NetTcpServer : public ITcpServer
{
private:
    int sockfd;                                                //监听套接字描述符
    int connfd;                                                //客户端连接套接字描述符
    struct sockaddr_in my_addr;                                //服务端进程地址信息
    struct sockaddr_in remote_addr;                            //客户端地址
    bool connet = false;                                       //是否与远程客户端连接上
    std::shared_ptr<std::map<char *, bool>> remotes = nullptr; //远程客户端列表

public:
    NetTcpServer();
    ~NetTcpServer();
    virtual bool createSocket() override;            //创建socket
    virtual void setReusePort() override;            //设置端口可重用
    virtual bool bindSocket() override;              //绑定到IP地址
    virtual bool listenSocket() override;            //简单socket套接字
    virtual void acceptRemote() override;            //接收客户端连接
    virtual bool receive() override;                 //接收到客户端数据
    virtual bool sendToRemote() override;            //发送数据给客户端
    virtual void closeRemote(int remotefd) override; //关闭客户端远程连接
    virtual void close();                            //关闭服务端连接
    virtual void add(char *ip) override;             //添加到容器
    virtual void remove(char *ip) override;          //从容器移除
};
#endif