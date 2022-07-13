#ifndef SERVER_SOCKET_MANAGER_H
#define SERVER_SOCKET_MANAGER_H

#include "../Global.h"
#include "./HandleThread.h"
#include "./HostnameTranslation.h"

#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

//先声明类,后面再定义
class HandleThread;

/**
 * @brief 服务端套接字多线程管理者
 *
 */
class TCPServerManager
{
private:
    int sockfd;                                               //监听套接字描述符
    int connfd;                                               //客户端连接套接字描述符
    struct sockaddr_in my_addr;                               //服务端进程地址信息
    struct sockaddr_in remote_addr;                           //客户端地址
    bool iSconneted = false;                                  //是否与远程客户端连接上
    std::shared_ptr<std::map<int, char *>> remotes = nullptr; //远程客户端列表

public:
    TCPServerManager();
    ~TCPServerManager();
    bool createSocket();                    //创建套接字
    bool bindSocket();                      //绑定端口
    bool listenSocket();                    //监听套接字
    void acceptSocket();                    //接收客户端连接
    void receiveRemote();                   //接收客户端消息
    bool sendRemote(int connfd, char *msg); //发送消息给客户端
    void closeRemote(int remotefd);         //关闭客户端
    void closeSelf();                       //关闭服务端
    void add(int connfd, char *ip);         //添加到容器
    void remove(int connfd);                //从容器移除
    bool isConnect();                       //是否连接上客户端
};
#endif