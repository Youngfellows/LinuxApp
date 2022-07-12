#ifndef NET_TCP_CLIENT_H
#define NET_TCP_CLIENT_H

#include "../Global.h"
#include "./HostnameTranslation.h"
#include "../interface/ITcpClient.h"

/**
 * @brief 派生类: TCP客户端
 *
 */
class NetTcpClient : public ITcpClient
{
private:
    int sockdf;                    //服务端socket套接字描述符
    char remoteIp[30];             //服务端IP地址
    struct sockaddr_in serverAddr; //服务端地址
    bool isConnect;                  //是否连接上

public:
    NetTcpClient();
    ~NetTcpClient();
    virtual bool createSocket() override;              //创建socket套接字
    virtual bool connectServer() override;             //连接服务端
    virtual void receive() override;                   //接收服务端消息
    virtual bool sendToRemote(char *message) override; //发送到服务端
    virtual void closeRemote() override;               //关闭与服务端连接
    virtual bool isConnected() override;               //是否连接上
};
#endif