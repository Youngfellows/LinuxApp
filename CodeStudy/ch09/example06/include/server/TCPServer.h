#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include "../interface/ITCPServer.h"
#include "./RemoteInfo.h"
#include "./NetUtil.h"

/**
 * @brief TCP服务端
 *
 */
class TCPServer : public ITCPServer
{
private:
    int mSockfd;                                               //服务端套接字描述符
    std::shared_ptr<std::map<int, char *>> mConnfds = nullptr; //连接的客户端列表
    struct sockaddr_in mServerAddr;                            //服务器段地址结构体
    pthread_mutex_t mMutex;                                    //线程互斥锁
    char *mInputBuffer = nullptr;                              //输入缓冲区

public:
    TCPServer();
    ~TCPServer();
    virtual bool create() override;
    virtual bool bindSocket() override;
    virtual bool listenSocket() override;
    virtual void acceptSocket() override;
    virtual int receive(int sockfd, void *buffer, int size) override;
    virtual bool sendSocket(int sockfd, void *buffer, size_t size) override;
    virtual char *input() override;
    virtual void closeSocket(int sockfd) override;
    virtual void destroy() override;
    virtual char *getIP(struct sockaddr_in *addr) override;

private:
    void threadProcess(int connfd, char *remoteIp); //线程回调函数
    void addConnfd(int connfd, char *remoteIp);
    void removeConnfd(int connfd);
};

#endif