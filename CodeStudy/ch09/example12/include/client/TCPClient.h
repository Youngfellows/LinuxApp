#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include "../interface/ITCPClient.h"

/**
 * @brief TCP客户端
 *
 */
class TCPClient : public ITCPClient
{
private:
    int mSockfd;                    //服务端套接字描述符
    struct sockaddr_in mServerAddr; //服务器段地址结构体
    char *mInputBuffer = nullptr;   //输入缓冲区

public:
    TCPClient();
    ~TCPClient();
    virtual bool connectServer() override;
    virtual bool create() override;
    virtual bool connectSocket(char *serverIp) override;
    virtual int receive(int sockfd, void *buffer, size_t size) override;
    virtual bool sendSocket(int sockfd, void *buffer, size_t size) override;
    virtual char *input() override;
    virtual void inputAndSend() override;
    virtual void closeSocket(int sockfd) override;
    virtual void destroy() override;
    virtual char *getIP(struct sockaddr_in *addr) override;
    virtual int parse(char *buf, char **args) override;
    virtual void processMenu() override;
    virtual void processExit(struct sockaddr_in addr) override;
    virtual void processLs(struct sockaddr_in addr, char *cmd) override;
    virtual void processGet(struct sockaddr_in addr, char *cmd) override;
    virtual void processPut(struct sockaddr_in addr, char *cmd) override;
};
#endif