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
    // getchar();                                                //吸收一个空格
    printf("*************\n");
    return mInputBuffer;
}

void TCPClient::inputAndSend()
{
    printf("输入客户端发送内容:");
    char *iMsg = input(); //输入要发送的内容
    // printf("%s\n", iMsg);
    sendSocket(mSockfd, iMsg, strlen(iMsg));                 //向服务端发送消息
    char *buffer = (char *)malloc(CACHESIZE * sizeof(char)); //动态申请缓冲区内存
    while (true)
    {
        int recvbytes = receive(mSockfd, buffer, CACHESIZE);
        if (recvbytes > 0)
        {
            buffer[recvbytes] = '\0'; //设置字符串结束标志
            cout << "服务端说:" << buffer << endl;
            printf("输入客户端发送内容:");
            iMsg = input();                          //输入要发送的内容
            sendSocket(mSockfd, iMsg, strlen(iMsg)); //向服务端发送消息
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