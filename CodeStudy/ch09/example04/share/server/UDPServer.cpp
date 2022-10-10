#include "../../include/server/UDPServer.h"

UDPServer::UDPServer()
{
    cout << "UDPServer()构造函数 ..." << endl;
    this->mInputBuffer = (char *)malloc(CACHESIZE * sizeof(char)); //动态申请内存
    this->mCacheBuffer = (char *)malloc(CACHESIZE * sizeof(char)); //动态申请内存
}

UDPServer::~UDPServer()
{
    cout << "~UDPServer()析构函数 ..." << endl;
}

/**
 * @brief 纯虚函数,抽象接口
 * @brief 创建UDP服务端
 *
 * @return true 创建UDP服务端成功
 * @return false 创建UDP服务端失败
 */
bool UDPServer::create()
{
    this->mSockfd = socket(AF_INET, SOCK_STREAM, 0); //创建socket套接字
    if (mSockfd == -1)
    {
        perror("create sockfd failed");
        return false;
    }
    int val = 1;
    setsockopt(mSockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&val, sizeof(val)); //设置地址端口可以重用
    return true;
}

/**
 * @brief 纯虚函数,抽象接口
 * @brief 绑定地址到套接字描述符上
 *
 * @return true 绑定地址到套接字描述符上成功
 * @return false 绑定地址到套接字描述符上失败
 */
bool UDPServer::bindSocket()
{
    //设置本地地址信息
    bzero(&mServerAddr, sizeof(mServerAddr));                  //填充0
    mServerAddr.sin_family = AF_INET;                          //协议族
    mServerAddr.sin_port = htons(SERVPORT);                    //端口
    mServerAddr.sin_addr.s_addr = inet_addr(NetUtil::getIP()); // IP地址
    // bzero(&(mServerAddr.sin_zero), 8);                         //填充0
    int ret = bind(mSockfd, (struct sockaddr *)&mServerAddr, sizeof(struct sockaddr));
    if (ret == -1)
    {
        perror("bind address failed");
        return false;
    }
    cout << "bind socket: " << NetUtil::getIP() << ":" << SERVPORT << endl;
    return true;
}

/**
 * @brief 纯虚函数,抽象接口
 * @brief 接收客户端连接
 */
void UDPServer::acceptSocket()
{
    struct sockaddr_in clientAddr;            //客户端地址
    int clentAddrLen;                         //客户端地址长度
    int sinSize = sizeof(struct sockaddr_in); //客户端地址长度

    while (true)
    {
        //接收UDP客户端的发送过来的数据
        memset(mCacheBuffer, 0, CACHESIZE * sizeof(char)); //清空缓冲区
        int number = recvfrom(mSockfd, mCacheBuffer, 0, (struct sockaddr *)&clientAddr, (socklen_t *)&clentAddrLen);
        // int number = recvfrom(mSockfd, mCacheBuffer, 0, (struct sockaddr *)&clientAddr, &sinSize);
        if (number < 0)
        {
            perror("recvfrom error");
            exit(1); //结束进程
        }
        mCacheBuffer[number] = '\0';
        printf("你接收到%s的消息:%s\n", getIP(&clientAddr), mCacheBuffer);
        char *iMsg = input(); //输入要发送的内容
    }
}

/**
 * @brief 线程回调函数
 *
 * @param arg 向线程传递的参数
 * @return void*
 */
void UDPServer::threadProcess(int connfd, char *remoteIp)
{
    cout << "ThreadId:" << pthread_self() << ",connfd:" << connfd << ",IP:" << remoteIp << endl;
    char *buffer = (char *)malloc(CACHESIZE * sizeof(char)); //动态申请缓冲区内存
    while (true)
    {
        int recvbytes = receive(connfd, buffer, CACHESIZE);
        if (recvbytes > 0)
        {
            buffer[recvbytes] = '\0'; //设置字符串结束标志
            cout << "客户端说:" << buffer << endl;
            printf("回客户端:");
            char *iMsg = input();                   //输入要回复的消息
            sendSocket(connfd, iMsg, strlen(iMsg)); //测试,原样返回
        }
    }
}

/**
 * @brief 纯虚函数,抽象接口
 * @brief 服务端接收客户端消息
 *
 * @param sockfd socket套接字描述符
 * @param buffer 缓冲区
 * @param size 缓冲区大小
 * @return int 返回接收的有效自己数
 */
int UDPServer::receive(int sockfd, void *buffer, int size)
{
    int recvbytes = recv(sockfd, (char *)buffer, size, 0); //接收客户端发送过来的消息
    if (recvbytes == -1)
    {
        perror("receive sockfd failed");
        removeConnfd(sockfd); //接收数据异常,移除客户端连接列表
        return -1;
    }
    return recvbytes;
}

char *UDPServer::input()
{
    memset(mInputBuffer, 0, CACHESIZE * sizeof(char));        //清空缓冲区
    fgets(mInputBuffer, CACHESIZE * sizeof(char) - 1, stdin); //输入字符串
    // getchar();                                                //吸收一个空格
    printf("^^^^^^^^^^^\n");
    return mInputBuffer;
}

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
bool UDPServer::sendSocket(int sockfd, void *buffer, size_t size)
{
    int res = send(sockfd, (char *)buffer, size, 0); //向客户端发送消息
    if (res == -1)
    {
        perror("send message failed");
        return false;
    }
    return true;
}

/**
 * @brief 纯虚函数,抽象接口
 * @brief 关闭socket套接字描述符
 *
 * @param sockfd socket套接字描述符
 */
void UDPServer::closeSocket(int sockfd)
{
    close(sockfd); //关闭socket套接字描述符
    removeConnfd(sockfd);
}

/**
 * @brief 纯虚函数,抽象接口
 * @brief 销毁TCP服务端
 */
void UDPServer::destroy()
{
    closeSocket(mSockfd);
    for (auto iter = mConnfds->begin(); iter != mConnfds->end(); iter++)
    {
        int sockfd = iter->first;
        closeSocket(sockfd);
    }
    mConnfds->clear(); //清空容器
}

/**
 * @brief 纯虚函数,抽象接口
 * @brief 获取IP地址的字符串形式
 *
 * @param addr
 * @return char* 返回IP地址的字符串形式
 */
char *UDPServer::getIP(struct sockaddr_in *addr)
{
    return inet_ntoa(addr->sin_addr);
}