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
    const char *pdir = "./file/";
    printf("输入要下载的文件名:");
    char *iMsg = input(); //输入要发送的内容
    // printf("%s\n", iMsg);
    sendSocket(mSockfd, iMsg, strlen(iMsg));                 //向服务端发送消息
    char *buffer = (char *)malloc(CACHESIZE * sizeof(char)); //动态申请缓冲区内存
    char *filename = new char[strlen(iMsg) - 1];             //文件名
    strncpy(filename, iMsg, strlen(iMsg) - 1);
    printf("长度:%ld,文件名:%s****\n", strlen(filename), filename);
    char *pathname = new char[strlen(pdir) + strlen(filename) + 1];
    sprintf(pathname, "%s%s", pdir, filename); //字符串拼接
    // const char *pathname = "./file/f1.txt";
    printf("长度:%ld,文件路径:%s\n", strlen(pathname), pathname);
    char *sign = "finish";
    int fd = open(pathname, O_CREAT | O_RDWR | O_TRUNC, 0644); //打开文件
    if (fd == -1)
    {
        perror("open file error");
        return;
    }
    int recvbytes = 0;
    memset(buffer, 0, CACHESIZE); //清空缓冲区
    while ((recvbytes = receive(mSockfd, buffer, CACHESIZE)) > 0)
    {
        printf("%d:: %s\n", recvbytes, buffer);
        if (recvbytes > 0)
        {
            write(fd, buffer, recvbytes); //向文件写入内容
        }
        memset(buffer, 0, CACHESIZE); //清空缓冲区
        char *dest = new char[strlen(sign)];
        // strncopy(buffer, dest, recvbytes - strlen(sign)); //拷贝结束字符串
        // printf("%s\n", dest);
        if (strcmp(sign, buffer) == 0)
        {
            printf("break\n");
            break;
        }
    }
    close(fd); //关闭文件
    printf("下载完成\n");
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

/**
 * @brief 纯虚函数,抽象接口
 * @brief 拷贝字符串
 *
 * @param s 原字符串
 * @param d 目标字符串
 * @param m 跳过的字节数
 */
void TCPClient::strncopy(char *s, char *d, int m)
{
    int n = 0;
    while (n < m - 1)
    {
        n++;
        s++;
    }
    while (*s != '\0')
    {
        *d = *s;
        s++;
        d++;
    }
}