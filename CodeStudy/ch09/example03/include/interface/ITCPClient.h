#ifndef ITCP_CLIENT_H
#define ITCP_CLIENT_H

#include "../Global.h"

/**
 * @brief 抽象类: 抽象TCP客户端
 *
 */
class ITCPClient
{
public:
    virtual ~ITCPClient() = default;

    /**
     * @brief 纯虚函数,抽象接口
     * @brief 创建TCP客户端
     *
     * @return true 创建TCP客户端成功
     * @return false 创建TCP客户端失败
     */
    virtual bool create() = 0;

    /**
     * @brief 纯虚函数,抽象接口
     * @brief 客户端向服务端发起连接请求
     *
     * @return true 连接请求成功
     * @return false 连接请求失败
     */
    virtual bool connect() = 0;

    /**
     * @brief 纯虚函数,抽象接口
     * @brief 服务端接收客户端消息
     *
     * @param sockfd socket套接字描述符
     * @param buffer 缓冲区
     * @param size 缓冲区大小
     * @return int 返回接收的有效自己数
     */
    virtual int receive(int sockfd, void *buffer, size_t size) = 0;

    /**
     * @brief 纯虚函数,抽象接口
     * @brief 服务端向客户端发送消息
     *
     * @param sockfd  socket套接字描述符
     * @param buffer 发送的消息内容
     * @param size 发送的消息大小
     * @return true 发送消息成功
     * @return false 发送消息失败
     */
    virtual bool send(int sockfd, void *buffer, size_t size) = 0;

    /**
     * @brief 纯虚函数,抽象接口
     * @brief 关闭socket套接字描述符
     *
     * @param sockfd socket套接字描述符
     */
    virtual void close(int sockfd) = 0;

    /**
     * @brief 纯虚函数,抽象接口
     * @brief 销毁TCP客户端
     */
    virtual void destroy() = 0;

    /**
     * @brief 纯虚函数,抽象接口
     * @brief 获取IP地址的字符串形式
     *
     * @param addr
     * @return char* 返回IP地址的字符串形式
     */
    virtual char *getIP(struct sockaddr_in *addr) = 0;
};

#endif