#ifndef ITCP_CLIENT_H
#define ITCP_CLIENT_H

/**
 * @brief 抽象TCP客户端
 *
 */
class ITcpClient
{
public:
    virtual ~ITcpClient() = default;
    virtual bool createSocket() = 0;              //创建socket套接字
    virtual bool connectServer() = 0;             //连接服务端
    virtual void receive() = 0;                   //接收服务端消息
    virtual bool sendToRemote(char *message) = 0; //发送到服务端
    virtual void closeRemote() = 0;               //关闭与服务端连接
    virtual bool isConnected() = 0;               //是否连接上
};

#endif