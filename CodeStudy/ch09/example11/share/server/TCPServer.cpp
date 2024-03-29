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
    int fd = -1;                                             //上传文件的文件描述符
    while (true)
    {
        memset(buffer, 0, CACHESIZE * sizeof(char));
        int recvbytes = receive(connfd, buffer, CACHESIZE);
        if (recvbytes > 0)
        {
            // buffer[recvbytes] = '\0'; //设置字符串结束标志
            // cout << "客户端说:" << buffer << endl;
            // printf("回客户端:");
            // char *iMsg = input();                   //输入要回复的消息
            // sendSocket(connfd, iMsg, strlen(iMsg)); //测试,原样返回
            if (isUpload)
            {
                if (strncmp(buffer, "#end#", 3) == 0)
                {
                    isUpload = false;
                    close(fd); //关闭文件
                    fd = -1;
                }
                else
                {
                    processPut(fd, buffer); //把数据写入文件
                }
            }
            else
            {
                if (strncmp(buffer, "ls", 2) == 0)
                {
                    processLs(connfd);
                }
                else if (strncmp(buffer, "get", 3) == 0)
                {
                    processGet(connfd, buffer);
                }
                else if (strncmp(buffer, "put", 3) == 0)
                {
                    isUpload = true;
                    char *fileName = parseFileName(buffer);
                    printf("文件名:%s\n", fileName);
                    fd = open(fileName, O_CREAT | O_WRONLY | O_TRUNC, 0644); //创建文件并打开
                    if (fd == -1)
                    {
                        perror("open file failed");
                        isUpload = false;
                    }
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

int TCPServer::parse(char *buf, char **args)
{
    int num = 0;
    while (*buf != '\0')
    {
        while ((*buf == ' ') || (*buf == '\t') || (*buf == '\n'))
        {
            *buf++ = '\0';
        }
        *args++ = buf;
        ++num;
        while ((*buf != '\0') && (*buf != ' ') && (*buf != '\t') && (*buf != '\n'))
        {
            buf++;
        }
    }
    *args = nullptr;
    return num;
}

char *TCPServer::parseFileName(char *cmd)
{
    char *cmds[N];                 //命令行参数字符串数组
    int number = parse(cmd, cmds); //解析命令行参数
    if (number < 2)
    {
        return nullptr;
    }
    // char *pathname = (char *)malloc(strlen(cmds[1]) * sizeof(char)); //动态申请内存
    // strcpy(pathname, cmds[1]);                                       //拷贝字符串到内存
    return cmds[1];
}

void TCPServer::processLs(int sockfd)
{
    printf("TCPServer::processLs():: start ...\n");
    DIR *myDir = nullptr;                                    //目录
    struct dirent *myItem = nullptr;                         //目录项
    char *buffer = (char *)malloc(CACHESIZE * sizeof(char)); //动态申请内存
    memset(buffer, 0, CACHESIZE * sizeof(char));             //清空缓冲区
    bzero(buffer, CACHESIZE * sizeof(char));
    if ((myDir = opendir(".")) == nullptr)
    {
        perror("opendir failed");
        return;
    }
    while ((myItem = readdir(myDir)) != nullptr)
    {
        if (sprintf(buffer, myItem->d_name, CACHESIZE * sizeof(char)) < 0)
        {
            printf("sprintf error");
            break;
        }
        printf("%s\n", buffer);
        sendSocket(sockfd, buffer, strlen(buffer)); //向客户端发送
        bzero(buffer, CACHESIZE * sizeof(char));
    }
    closedir(myDir);
    char *end = "#end#";
    sendSocket(sockfd, end, strlen(end)); //发送结束标志
    printf("TCPServer::processLs():: end ...\n");
}

void TCPServer::processGet(int sockfd, char *buffer)
{
    char *pathname = parseFileName(buffer);
    int fd = open(pathname, O_RDONLY); //打开文件
    if (fd == -1)
    {
        perror("process get failed");
        return;
    }
    int number = 0;
    char *cacheBuffer = (char *)malloc(CACHESIZE * sizeof(char)); //动态申请内存
    memset(cacheBuffer, 0, CACHESIZE * sizeof(char));             //清空缓冲区
    while ((number = read(fd, cacheBuffer, CACHESIZE)) > 0)
    {
        sendSocket(sockfd, cacheBuffer, number); //向客户端发送读取到的文件
        // bzero(cacheBuffer, CACHESIZE * sizeof(char));
        memset(cacheBuffer, 0, CACHESIZE * sizeof(char)); //清空缓冲区
    }
    char *end = "#end#";
    sendSocket(sockfd, end, strlen(end)); //发送结束标志
    close(fd);                            //关闭文件
}

void TCPServer::processPut(int fd, char *buffer)
{
    if (write(fd, buffer, strlen(buffer)) < 0) //向文件写入内容
    {
        perror("process put write failed");
        close(fd);
    }
}