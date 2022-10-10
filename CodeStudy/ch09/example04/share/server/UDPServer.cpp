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
        receive(mSockfd, mCacheBuffer, CACHESIZE, (struct sockaddr *)&clientAddr, (socklen_t *)&clentAddrLen);
        printf("你接收到%s的消息:%s\n", getIP(&clientAddr), mCacheBuffer);
        char *iMsg = input(); //输入要发送的内容
        sendSocket(mSockfd, iMsg, strlen(iMsg), (struct sockaddr *)&clientAddr, sinSize);
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
int UDPServer::receive(int sockfd, void *buffer, int size, struct sockaddr *from, socklen_t *fromlen)
{
    //接收UDP客户端的发送过来的数据
    memset(buffer, 0, CACHESIZE * sizeof(char)); //清空缓冲区
    int recvbytes = recvfrom(sockfd, (char *)buffer, CACHESIZE, 0, from, fromlen);
    if (recvbytes < 0)
    {
        perror("recvfrom error");
        exit(1); //结束进程
    }
    mCacheBuffer[recvbytes] = '\0';
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
bool UDPServer::sendSocket(int sockfd, void *buffer, size_t size, struct sockaddr *to, socklen_t tolen)
{
    int res = sendto(sockfd, (char *)buffer, size, 0, to, tolen); //向客户端发送消息
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
}

/**
 * @brief 纯虚函数,抽象接口
 * @brief 销毁TCP服务端
 */
void UDPServer::destroy()
{
    closeSocket(mSockfd);
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