#include "../../include/server/NetTcpServer.h"

NetTcpServer::NetTcpServer()
{
    cout << "NetTcpServer()构造函数" << endl;
    this->remotes = std::make_shared<std::map<int, char *>>();
}

NetTcpServer::~NetTcpServer()
{
    cout << "~NetTcpServer()析构函数" << endl;
}

/**
 * @brief 创建套接字
 *
 * @return true 创建套接字成功
 * @return false 创建套接字失败
 */
bool NetTcpServer::createSocket()
{
    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    cout << "NetTcpServer::createSocket():: sockfd:" << this->sockfd << endl;
    if (this->sockfd == -1)
    {
        //失败
        return false;
    }
    return true;
}

/**
 * @brief 设置端口可重用
 *
 */
void NetTcpServer::setReusePort()
{
    int val = 1;
    setsockopt(this->sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&val, sizeof(val));
}

/**
 * @brief 设置本地地址信息,并绑定到socket套接字描述符
 *
 * @return true
 * @return false
 */
bool NetTcpServer::bindSocket()
{
    // IP地址与主机名相互转化
    std::shared_ptr<HostnameTranslation> translation = std::make_shared<HostnameTranslation>();
    char *hostname = translation->getHostName();
    char *ip = translation->translateIP(hostname);
    cout << "NetTcpServer::bindSocket():: IP:" << ip << endl;
    // translation->translateHostname(ip);

    this->my_addr.sin_family = AF_INET;          //协议族
    this->my_addr.sin_port = htons(SERVER_PORT); //端口
    // this->my_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // IP地址
    this->my_addr.sin_addr.s_addr = inet_addr(ip); // IP地址
    // this->my_addr.sin_addr.s_addr = htonl(INADDR_ANY);      // IP地址
    bzero(&(this->my_addr.sin_zero), 8); //填充0

    //绑定地址到套接字描述符上
    int bindRes = bind(this->sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr));
    char *server = inet_ntoa(my_addr.sin_addr); //服务费IP地址
    cout << " NetTcpServer::bindSocket():: server ip:" << server << ", bindRes:" << bindRes << endl;
    if (bindRes == -1)
    {
        //绑定失败
        return false;
    }

    return true;
}

/**
 * @brief 在地址端口上监听
 *
 * @return true
 * @return false
 */
bool NetTcpServer::listenSocket()
{
    int listenRes = listen(this->sockfd, BACKLOG);
    cout << " NetTcpServer::listenSocket():: listenRes:" << listenRes << endl;
    if (listenRes == -1)
    {
        //监听失败
        return false;
    }
    return true;
}

/**
 * @brief 等待客户端连接，如果有新的客户端连接，则产生新的连接套接字
 *
 * @return true
 * @return false
 */
void NetTcpServer::acceptRemote()
{
    while (true)
    {
        socklen_t sin_size = sizeof(struct sockaddr_in);
        int newConnfd = accept(this->sockfd, (struct sockaddr *)&remote_addr, &sin_size);
        char *remote = inet_ntoa(remote_addr.sin_addr);
        cout << "NetTcpServer::acceptRemote():: remote ip:" << remote << ",connfd:" << this->connfd << endl;
        if (newConnfd == -1)
        {
            //连接断开或者异常
            // cout << "服务端与远程客户端" << remote << "断开链接" << endl;
            this->remove(newConnfd);
        }
        else
        {
            //保证只有一个连接,不处理多连接
            if (newConnfd != this->connfd)
            {
                //把旧的已经连接的断开
                this->remove(this->connfd);
                closeRemote(this->connfd);
                this->connfd = newConnfd; //新的连接
            }

            //加如到已经连接容器列表中
            cout << "服务端与远程客户端IP:" << remote << "建立链接成功,connfd:" << this->connfd << endl;
            this->add(this->connfd, remote);
            if (this->isConnect())
            {
                //接收客户端数据,开启多线程处理每一个远程客户端连接
                this->receive(this->connfd, remote_addr);
                // std::shared_ptr<ITcpServer> pServer(this);
                // std::shared_ptr<IHandleThread> handleThread = std::make_shared<HandleThread>();
                // handleThread->start(this->connfd, remote_addr);
            }
        }
    }
}

void NetTcpServer::add(int connfd, char *ip)
{
    auto iter = this->remotes->find(connfd);
    if (iter == this->remotes->end())
    {
        this->remotes->insert(std::pair<int, char *>(connfd, ip));
        cout << "NetTcpServer::add():: 保存connfd:" << connfd << ",IP:" << ip << ",到已连接列表" << endl;
    }
    else
    {
        cout << "NetTcpServer::add()::  connfd:" << connfd << ",IP:" << ip << ",已经保存到了已连接列表,不要再插入了 ..." << endl;
    }
}

void NetTcpServer::remove(int connfd)
{
    auto iter = this->remotes->find(connfd);
    if (iter != this->remotes->end())
    {
        char *ip = iter->second;
        this->remotes->erase(iter);
        cout << "NetTcpServer::remote():: 从已连接列表删除IP:" << ip << ",connfd:" << connfd << endl;
    }
    else
    {
        // cout << "NetTcpServer::remote():: 已连接列表不存在IP:" << ip << ",无需要删除" << endl;
    }
}

/**
 * @brief 是否与客户端连接上
 *
 * @return true 连接上
 * @return false 没有连接上
 */
bool NetTcpServer::isConnect()
{
    int size = this->remotes->size();
    this->connet = size > 0;
    cout << "NetTcpServer::isConnect():: size:" << size << ",connet:" << this->connet << endl;
    return this->connet;
}

/**
 * @brief 接收客户端数据
 * @brief 开启多线程处理每一个远程客户端连接,否则可能出现一直阻塞的现象,新的客户端连接过来了,可以关闭掉旧的客户端
 *
 * @param connfd 客户端套接字描述符
 * @param client 客户端地址
 * @return true
 * @return false
 */
bool NetTcpServer::receive(int connfd, struct sockaddr_in client)
{
    char *remote = inet_ntoa(remote_addr.sin_addr);
    cout << "NetTcpServer::receive():: remote ip:" << remote << ",connfd:" << this->connfd << endl;
    int receiveNum = 0;                //接收数据大小
    char receiveBuffer[MAX_DATA_SIZE]; //接收数据缓冲区

    receiveNum = recv(connfd, receiveBuffer, MAX_DATA_SIZE, 0);
    if (receiveNum == -1)
    {
        //接收数据异常,关闭连接
        cout << "NetTcpServer::receive():: 1,接收数据异常,remote ip:" << remote << ",connfd:" << this->connfd << endl;
        this->remove(connfd);
        this->closeRemote(connfd);
        return false;
    }
    else
    {
        cout << "NetTcpServer::receive():: 1,接收到,receiveNum:" << receiveNum << ",receiveBuffer:" << receiveBuffer << endl;
        //字符串拼接
        char sendBuf[MAX_DATA_SIZE];
        strcpy(sendBuf, receiveBuffer);
        // strcat("杨过说,", sendBuf);
        cout << "send:" << sendBuf << endl;
        this->sendToRemote(connfd, sendBuf);
    }

    //循环接收数据
    while ((receiveNum = recv(connfd, receiveBuffer, MAX_DATA_SIZE, 0)))
    {
        cout << "NetTcpServer::receive():: 2,接收到,receiveNum:" << receiveNum << ",receiveBuffer:" << receiveBuffer << endl;
        //字符串拼接
        char sendBuf[MAX_DATA_SIZE];
        strcpy(sendBuf, receiveBuffer);
        // strcat("杨过说,", sendBuf);
        cout << "send:" << sendBuf << endl;
        this->sendToRemote(connfd, sendBuf);
    }
    //接收数据异常,关闭连接
    cout << "NetTcpServer::receive():: 2,接收数据异常,remote ip:" << remote << ",connfd:" << this->connfd << endl;
    this->remove(connfd);
    this->closeRemote(connfd);
    return true;
}

/**
 * @brief 发送数据给客户端
 *
 * @param connfd 客户端套接字描述符
 * @param msg 发送的消息
 * @return true
 * @return false
 */
bool NetTcpServer::sendToRemote(int connfd, char *msg)
{
    int res = send(connfd, msg, MAX_DATA_SIZE, 0);
    cout << "NetTcpServer::sendToRemote():: res:" << res << endl;
    if (res == -1)
    {
        return false;
    }
    return true;
}

void NetTcpServer::closeRemote(int remotefd)
{
    close(remotefd); //关闭远程连接
}

void NetTcpServer::closeServer()
{
}