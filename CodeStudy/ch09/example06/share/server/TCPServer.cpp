#include "../../include/server/TCPServer.h"

TCPServer::TCPServer()
{
    cout << "TCPServer()构造函数 ..." << endl;
    this->mInputBuffer = (char *)malloc(CACHESIZE * sizeof(char)); //动态申请内存
    this->mConnfds = std::make_shared<std::map<int, char *>>();    //初始化容器列表
    pthread_mutex_init(&mMutex, nullptr);                          //初始化互斥锁
}

TCPServer::~TCPServer()
{
    cout << "~TCPServer()析构函数 ..." << endl;
}

/**
 * @brief 纯虚函数,抽象接口
 * @brief 创建TCP服务端
 *
 * @return true 创建TCP服务端成功
 * @return false 创建TCP服务端失败
 */
bool TCPServer::create()
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
bool TCPServer::bindSocket()
{
    //设置本地地址信息
    mServerAddr.sin_family = AF_INET;                          //协议族
    mServerAddr.sin_port = htons(SERVPORT);                    //端口
    mServerAddr.sin_addr.s_addr = inet_addr(NetUtil::getIP()); // IP地址
    bzero(&(mServerAddr.sin_zero), 8);                         //填充0
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
 * @brief 在地址端口上监听
 *
 * @return true 在地址端口上监听成功
 * @return false 在地址端口上监听失败
 */
bool TCPServer::listenSocket()
{
    int ret = listen(mSockfd, BACKLOG); //在地址端口上监听
    if (ret == -1)
    {
        perror("listen sockfd failed");
        return false;
    }
    return true;
}

/**
 * @brief 纯虚函数,抽象接口
 * @brief 接收客户端连接
 */
void TCPServer::acceptSocket()
{
    struct sockaddr_in clientAddr; //客户端地址
    int clentAddrLen;              //客户端地址长度

    while (true)
    {
        //等待客户端连接,如果有客户端连接,则产生新的连接套接字
        int connfd = accept(mSockfd, (struct sockaddr *)&clientAddr, (socklen_t *)&clentAddrLen);
        if (connfd == -1)
        {
            perror("accept client failed");
            removeConnfd(connfd);
        }
        else
        {
            char *ip = getIP(&clientAddr); //获取客户端IP地址
            RemoteInfo remoteInfo;
            remoteInfo.connfd = connfd;
            strcpy(remoteInfo.ip, ip);
            cout << "客户端:" << remoteInfo.ip << ",connfd:" << remoteInfo.connfd << ",连接成功了 ..." << endl;
            addConnfd(connfd, ip);
            std::thread handleThread = std::thread([this](int &connfd, char *remoteIp)
                                                   { this->threadProcess(connfd, remoteIp); },
                                                   std::ref(connfd), std::ref(ip));
            handleThread.detach();
        }
    }
}

/**
 * @brief 添加已经连接的客户端到容器列表
 *
 * @param connfd 已经连接的客户端套接字描述符
 * @param remoteIp 客户端IP地址
 */
void TCPServer::addConnfd(int connfd, char *remoteIp)
{
    pthread_mutex_lock(&mMutex); //互斥锁上锁
    auto iter = mConnfds->find(connfd);
    if (iter == mConnfds->end())
    {
        mConnfds->insert(std::pair<int, char *>(connfd, remoteIp)); //连接的客户端添加到容器列表
        cout << "添加已经连接容器,客户端:" << remoteIp << ",connfd:" << connfd << endl;
    }
    else
    {
        cout << "连接容器已经存在,客户端:" << remoteIp << ",connfd:" << connfd << endl;
    }
    pthread_mutex_unlock(&mMutex); //互斥锁四方是
}

/**
 * @brief 从已经连接的容器中移除指定客户端
 *
 * @param connfd 客户端套接字描述符
 */
void TCPServer::removeConnfd(int connfd)
{
    pthread_mutex_lock(&mMutex); //互斥锁上锁
    auto iter = mConnfds->find(connfd);
    if (iter != mConnfds->end())
    {
        char *remoteIp = iter->second;
        mConnfds->erase(iter); //从容器移除元素
        cout << "从已经连接容器移除,客户端:" << remoteIp << ",connfd:" << connfd << endl;
    }
    else
    {
        cout << "不存在客户端connfd:" << connfd << endl;
    }
    pthread_mutex_unlock(&mMutex); //互斥锁四方是
}

/**
 * @brief 线程回调函数
 *
 * @param arg 向线程传递的参数
 * @return void*
 */
void TCPServer::threadProcess(int connfd, char *remoteIp)
{
    cout << "ThreadId:" << pthread_self() << ",connfd:" << connfd << ",IP:" << remoteIp << endl;
    char *buffer = (char *)malloc(CACHESIZE * sizeof(char)); //动态申请缓冲区内存
    const char *pdir = "../../file/";                        //父目录
    while (true)
    {
        int recvbytes = receive(connfd, buffer, CACHESIZE);
        if (recvbytes > 0)
        {
            // buffer[recvbytes] = '\0'; //设置字符串结束标志
            char *pathname = new char[strlen(pdir) + strlen(buffer) + 1];
            sprintf(pathname, "%s%s", pdir, buffer); //字符串拼接
            // const char *pathname = "../../file/f1.txt";
            cout << "文件名:" << pathname << endl;
            int fd = open(pathname, O_RDONLY); //打开文件
            if (fd == -1)
            {
                perror("open file failed");
                break;
            }
            else
            {
                char buf[100]; //缓冲区
                int number = 0;
                while ((number = read(fd, buf, 100)) > 0) //读文件
                {
                    sendSocket(connfd, buf, number); //向客户端发送文件
                }
            }
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
int TCPServer::receive(int sockfd, void *buffer, int size)
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

char *TCPServer::input()
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
bool TCPServer::sendSocket(int sockfd, void *buffer, size_t size)
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
void TCPServer::closeSocket(int sockfd)
{
    close(sockfd); //关闭socket套接字描述符
    removeConnfd(sockfd);
}

/**
 * @brief 纯虚函数,抽象接口
 * @brief 销毁TCP服务端
 */
void TCPServer::destroy()
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
char *TCPServer::getIP(struct sockaddr_in *addr)
{
    return inet_ntoa(addr->sin_addr);
}