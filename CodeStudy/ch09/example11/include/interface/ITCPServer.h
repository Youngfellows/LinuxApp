#ifndef ITCP_SERVER_H
#define ITCP_SERVER_H

#include "../Global.h"

/**
 * @brief 抽象类: 抽象TCP服务端
 *
 */
class ITCPServer
{
public:
    virtual ~ITCPServer() = default;

    /**
     * @brief 纯虚函数,抽象接口
     * @brief 创建TCP服务端
     *
     * @return true 创建TCP服务端成功
     * @return false 创建TCP服务端失败
     */
    virtual bool create() = 0;

    /**
     * @brief 纯虚函数,抽象接口
     * @brief 绑定地址到套接字描述符上
     *
     * @return true 绑定地址到套接字描述符上成功
     * @return false 绑定地址到套接字描述符上失败
     */
    virtual bool bindSocket() = 0;

    /**
     * @brief 纯虚函数,抽象接口
     * @brief 在地址端口上监听
     *
     * @return true 在地址端口上监听成功
     * @return false 在地址端口上监听失败
     */
    virtual bool listenSocket() = 0;

    /**
     * @brief 纯虚函数,抽象接口
     * @brief 接收客户端连接
     */
    virtual void acceptSocket() = 0;

    /**
     * @brief 纯虚函数,抽象接口
     * @brief 服务端接收客户端消息
     *
     * @param sockfd socket套接字描述符
     * @param buffer 缓冲区
     * @param size 缓冲区大小
     * @return int 返回接收的有效自己数
     */
    virtual int receive(int sockfd, void *buffer, int size) = 0;

    /**
     * @brief 纯虚函数,抽象接口
     * @brief 输入要向服务端发送的消息
     */
    virtual char *input() = 0;

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
    virtual bool sendSocket(int sockfd, void *buffer, size_t size) = 0;

    /**
     * @brief 纯虚函数,抽象接口
     * @brief 关闭socket套接字描述符
     *
     * @param sockfd socket套接字描述符
     */
    virtual void closeSocket(int sockfd) = 0;

    /**
     * @brief 纯虚函数,抽象接口
     * @brief 销毁TCP服务端
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

    /**
     *
     * @brief 解析命令行参数
     *
     * @param buf 命令行参数
     * @param args 命令行参数字符串数组
     * @return int 返回命令行参数字符串数组长度
     */
    virtual int parse(char *buf, char **args) = 0;

    /**
     * @brief 纯虚函数,抽象接口
     * @brief 获取服务端文件列表
     *
     * @param sockfd Socket套接字
     */
    virtual void processLs(int sockfd) = 0;

    /**
     * @brief 纯虚函数,抽象接口
     * @brief 获取服务端指定文件
     *
     * @param sockfd Socket套接字
     * @param fileName 要获取的文件名称
     */
    virtual void processGet(int sockfd, char *fileName) = 0;

    /**
     * @brief 纯虚函数,抽象接口
     * @brief 上传文件到服务端
     *
     * @param fd 文件描述符
     * @param fileName 上传的文件名称
     */
    virtual void processPut(int fd, char *fileName) = 0;
};

#endif