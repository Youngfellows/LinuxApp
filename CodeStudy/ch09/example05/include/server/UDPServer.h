#ifndef UDP_SERVER_H
#define UDP_SERVER_H

#include "../interface/IUDPServer.h"
#include "./NetUtil.h"

/**
 * @brief UDP服务端
 *
 */
class UDPServer : public IUDPServer
{
private:
    int mSockfd;                    //服务端套接字描述符
    struct sockaddr_in mServerAddr; //服务器段地址结构体
    char *mInputBuffer = nullptr;   //输入缓冲区
    char *mCacheBuffer = nullptr;   //接收数据缓冲区

public:
    UDPServer();
    ~UDPServer();
    virtual bool create() override;
    virtual bool bindSocket() override;
    virtual void acceptSocket() override;
    virtual int receive(int sockfd, void *buffer, int size, struct sockaddr *from, socklen_t *fromlen) override;
    virtual bool sendSocket(int sockfd, void *buffer, size_t size, struct sockaddr *to, socklen_t tolen) override;
    virtual char *input() override;
    virtual void closeSocket(int sockfd) override;
    virtual void destroy() override;
    virtual char *getIP(struct sockaddr_in *addr) override;
};

#endif