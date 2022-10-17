#include "../../include/client/TCPClient.h"

TCPClient::TCPClient()
{
    cout << "TCPClient()构造函数" << endl;
    this->mInputBuffer = (char *)malloc(CACHESIZE * sizeof(char)); //动态申请内存
}

TCPClient::~TCPClient()
{
    cout << "~TCPClient()析构函数" << endl;
    free(mInputBuffer); //释放内存
}

bool TCPClient::connectServer()
{
    bool res = this->create(); //创建Socket连接
    if (res)
    {
        res = this->connectSocket(nullptr); //客户端连接Socket服务端
        return res;
    }
    return false;
}

bool TCPClient::create()
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

bool TCPClient::connectSocket(char *serverIp)
{
    bzero(&mServerAddr, sizeof(mServerAddr)); //清空内存
    if (serverIp == nullptr)
    {
        serverIp = NetUtil::getIP(); //获取本机的IP地址
    }
    mServerAddr.sin_family = AF_INET;                                                     //协议族
    inet_pton(AF_INET, serverIp, &mServerAddr.sin_addr);                                  // IP地址
    mServerAddr.sin_port = htons(SERVPORT);                                               //端口
    int ret = connect(mSockfd, (struct sockaddr *)&mServerAddr, sizeof(struct sockaddr)); //连接服务端

    // mServerAddr.sin_family = AF_INET;                  //协议族
    // mServerAddr.sin_port = htons(SERVPORT);            //端口
    // mServerAddr.sin_addr.s_addr = inet_addr(serverIp); // IP地址
    // bzero(&(mServerAddr.sin_zero), 8);                 //填充0
    // int ret = connect(mSockfd, (struct sockaddr *)&mServerAddr, sizeof(struct sockaddr)); //连接服务端

    if (ret == -1)
    {
        perror("connect server error");
        return false;
    }
    return true;
}

int TCPClient::receive(int sockfd, void *buffer, size_t size)
{
    int recvbytes = recv(sockfd, (char *)buffer, size, 0); //接收客户端发送过来的消息
    if (recvbytes == -1)
    {
        perror("receive sockfd failed");
        return -1;
    }
    return recvbytes;
}

bool TCPClient::sendSocket(int sockfd, void *buffer, size_t size)
{
    int res = send(sockfd, (char *)buffer, size, 0); //向客户端发送消息
    if (res == -1)
    {
        perror("send message failed");
        return false;
    }
    return true;
}

char *TCPClient::input()
{
    memset(mInputBuffer, 0, CACHESIZE * sizeof(char));        //清空缓冲区
    fgets(mInputBuffer, CACHESIZE * sizeof(char) - 1, stdin); //输入字符串
    return mInputBuffer;
}

void TCPClient::inputAndSend()
{
    // printf("输入客户端发送内容:");
    // char *iMsg = input(); //输入要发送的内容
    // // printf("%s\n", iMsg);
    // sendSocket(mSockfd, iMsg, strlen(iMsg));                 //向服务端发送消息
    // char *buffer = (char *)malloc(CACHESIZE * sizeof(char)); //动态申请缓冲区内存
    // while (true)
    // {
    //     int recvbytes = receive(mSockfd, buffer, CACHESIZE);
    //     if (recvbytes > 0)
    //     {
    //         buffer[recvbytes] = '\0'; //设置字符串结束标志
    //         cout << "服务端说:" << buffer << endl;
    //         printf("输入客户端发送内容:");
    //         iMsg = input();                          //输入要发送的内容
    //         sendSocket(mSockfd, iMsg, strlen(iMsg)); //向服务端发送消息
    //     }
    // }

    while (true)
    {
        printf(">");
        char *cmd = input();
        if (cmd == nullptr)
        {
            printf("fgets error");
            break;
        }
        if (strlen(cmd) == 1)
        {
            continue;
        }
        cmd[strlen(cmd) - 1] = '\0';
        printf("<%s\n", cmd);
        if (strncmp(cmd, "help", 4) == 0)
        {
            processMenu();
        }
        else if (strncmp(cmd, "exit", 4) == 0)
        {
            processExit(mServerAddr);
            exit(0);
        }
        else if (strncmp(cmd, "ls", 2) == 0)
        {
            processLs(mServerAddr, cmd);
        }
        else if (strncmp(cmd, "get", 3) == 0)
        {
            processGet(mServerAddr, cmd);
        }
        else if (strncmp(cmd, "put", 3) == 0)
        {
            processPut(mServerAddr, cmd);
        }
        else
        {
            printf("输入命令错误,请重新输入\n");
        }
    }
}

void TCPClient::closeSocket(int sockfd)
{
    close(sockfd); //关闭socket套接字描述符
}

void TCPClient::destroy()
{
    closeSocket(mSockfd);
}

char *TCPClient::getIP(struct sockaddr_in *addr)
{
    return inet_ntoa(addr->sin_addr);
}

int TCPClient::parse(char *buf, char **args)
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

void TCPClient::processMenu()
{
    printf("\n--------------------------------------------\n");
    printf("| hele: 显示全部帮助命令\n");
    printf("| exit: 退出\n");
    printf("| ls  : 显示服务端文件名称列表\n");
    printf("| get 文件名: 下载服务端文件\n");
    printf("| put 文件名: 上传文件到服务端\n");
    printf("--------------------------------------------\n");
}

void TCPClient::processExit(struct sockaddr_in addr)
{
    char *byte = "Byte!";
    printf("%s\n", byte);
    sendSocket(mSockfd, byte, strlen(byte));
    closeSocket(mSockfd);
}

void TCPClient::processLs(struct sockaddr_in addr, char *cmd)
{
    sendSocket(mSockfd, cmd, strlen(cmd));
    char *buffer = (char *)malloc(CACHESIZE * sizeof(char)); //动态申请缓冲区内存
    int recvbytes = 0;
    while ((recvbytes = receive(mSockfd, buffer, CACHESIZE)) > 0)
    {
        printf("***%s", buffer);
        memset(buffer, 0, sizeof(buffer)); //清空内存
    }
    printf("\n");
    free(buffer);
}

void TCPClient::processGet(struct sockaddr_in addr, char *cmd)
{
    sendSocket(mSockfd, cmd, strlen(cmd));
    char *cmds[N];                 //命令行参数字符串数组
    int number = parse(cmd, cmds); //解析命令行参数
    if (number < 2)
    {
        return;
    }
    char *pathname = cmds[1]; //文件名
    // printf("文件名:%s\n", pathname);
    int fd = open(pathname, O_CREAT | O_WRONLY | O_TRUNC, 0644); //创建文件并打开
    if (fd == -1)
    {
        perror("open file error");
        return;
    }
    char *buffer = (char *)malloc(CACHESIZE * sizeof(char)); //动态申请缓冲区内存
    int recvbytes = 0;
    while ((recvbytes = receive(mSockfd, buffer, CACHESIZE)) > 0)
    {
        // printf("%s", buffer);
        write(fd, buffer, recvbytes);      //向文件写入内容
        memset(buffer, 0, sizeof(buffer)); //清空内存
    }
    printf("\n");
    close(fd);    //关闭文件
    free(buffer); //释放内存
}

void TCPClient::processPut(struct sockaddr_in addr, char *cmd)
{
    sendSocket(mSockfd, cmd, strlen(cmd));
    char *cmds[N];                 //命令行参数字符串数组
    int number = parse(cmd, cmds); //解析命令行参数
    if (number < 2)
    {
        return;
    }
    char *pathname = cmds[1]; //文件名
    // printf("文件名:%s\n", pathname);
    int fd = open(pathname, O_RDONLY); //打开文件
    if (fd == -1)
    {
        perror("open file failed");
        return;
    }
    char *buffer = (char *)malloc(CACHESIZE * sizeof(char)); //动态申请缓冲区内存
    int readbytes = 0;
    while ((readbytes = read(fd, buffer, CACHESIZE)) > 0) //读取文件内容并传递
    {
        sendSocket(mSockfd, buffer, readbytes); //向客户端传输文件内容
        memset(buffer, 0, sizeof(buffer));      //清空内存
    }
    char *end = "#end#";
    sendSocket(mSockfd, end, strlen(end)); //发送结束标志
    printf("\n");
    close(fd); //关闭文件
    free(buffer);
}