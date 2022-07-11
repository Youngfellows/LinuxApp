#ifndef ITCP_SERVER_H
#define ITCP_SERVER_H

/**
 * @brief 抽象TCP服务端接口
 *
 */
class ITcpServer
{
public:
    virtual ~ITcpServer() = default;
    virtual bool createSocket() = 0;            //创建socket
    virtual void setReusePort() = 0;            //设置端口可重用
    virtual bool bindSocket() = 0;              //绑定到IP地址
    virtual bool listenSocket() = 0;            //简单socket套接字
    virtual void acceptRemote() = 0;            //接收客户端连接
    virtual bool receive() = 0;                 //接收到客户端数据
    virtual bool sendToRemote() = 0;            //发送数据给客户端
    virtual void closeRemote(int remotefd) = 0; //关闭客户端远程连接
    virtual void close() = 0;                   //关闭服务端连接
    virtual void add(char *ip) = 0;             //添加到容器
    virtual void remove(char *ip) = 0;          //从容器移除
};

#endif