#include "../../include/server/TCPServerManager.h"

TCPServerManager::TCPServerManager()
{
    cout << "TCPServerManager()构造函数" << endl;
    this->remotes = std::make_shared<std::map<int, char *>>();
}

TCPServerManager::~TCPServerManager()
{
    cout << "~TCPServerManager()析构函数" << endl;
}

/**
 * @brief 创建套接字
 *
 * @return true
 * @return false
 */
bool TCPServerManager::createSocket()
{
    cout << "TCPServerManager::createSocket():: ..." << endl;
    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    cout << "TCPServerManager::createSocket():: sockfd:" << this->sockfd << endl;
    if (this->sockfd == -1)
    {
        //失败
        return false;
    }
    //设置端口可重用
    int val = 1;
    setsockopt(this->sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&val, sizeof(val));
    return true;
}

/**
 * @brief 绑定端口
 *
 * @return true
 * @return false
 */
bool TCPServerManager::bindSocket()
{
    cout << "TCPServerManager::bindSocket():: ..." << endl;
    // IP地址与主机名相互转化
    std::shared_ptr<HostnameTranslation> translation = std::make_shared<HostnameTranslation>();
    char *hostname = translation->getHostName();
    char *ip = translation->translateIP(hostname);
    cout << "TCPServerManager::bindSocket():: IP:" << ip << endl;
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
    cout << "TCPServerManager::bindSocket():: server ip:" << server << ", bindRes:" << bindRes << endl;
    if (bindRes == -1)
    {
        //绑定失败
        return false;
    }
    return true;
}

/**
 * @brief 监听套接字
 *
 * @return true
 * @return false
 */
bool TCPServerManager::listenSocket()
{
    cout << "TCPServerManager::listenSocket():: ..." << endl;
    int listenRes = listen(this->sockfd, BACKLOG);
    cout << "TCPServerManager::listenSocket():: listenRes:" << listenRes << endl;
    if (listenRes == -1)
    {
        //监听失败
        return false;
    }
    return true;
}

/**
 * @brief 接收客户端连接
 * @brief 开启多线程处理
 *
 */
void TCPServerManager::acceptSocket()
{
    cout << "TCPServerManager::acceptSocket():: ..." << endl;
    // for (int i = 0; i < 10; i++)
    // {
    //     //创建一个线程
    //     HandleThread *handlerThread = new HandleThread(this);
    //     handlerThread->start(); //启动多线程
    // }

    while (true)
    {
        cout << "TCPServerManager::acceptSocket():: 等待客户端连接 ..." << endl;
        socklen_t sin_size = sizeof(struct sockaddr_in);
        int newConnfd = accept(this->sockfd, (struct sockaddr *)&remote_addr, &sin_size);
        char *remote = inet_ntoa(remote_addr.sin_addr);
        cout << "NetTcpServer::acceptRemote():: remote ip:" << remote << ",connfd:" << this->connfd << ",newConnfd:" << newConnfd << endl;
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
                cout << "NetTcpServer::acceptRemote():: conect ..." << endl;
                //接收客户端数据,开启多线程处理每一个远程客户端连接
                // this->receive(this->connfd, remote_addr);

                //创建一个线程
                HandleThread *handlerThread = new HandleThread(this);
                handlerThread->start(); //启动多线程
            }
        }
    }
}

/**
 * @brief 接收客户端消息
 *
 */
void TCPServerManager::receiveRemote()
{
    cout << "TCPServerManager::receiveRemote():: ..." << endl;
    char *remote = inet_ntoa(remote_addr.sin_addr);
    cout << "TCPServerManager::receiveRemote():: remote ip:" << remote << ",connfd:" << this->connfd << endl;
    int receiveNum = 0;                //接收数据大小
    char receiveBuffer[MAX_DATA_SIZE]; //接收数据缓冲区

    while (true)
    {
        receiveNum = recv(this->connfd, receiveBuffer, MAX_DATA_SIZE, 0);
        cout << "TCPServerManager::receiveRemote():: receiveNum:" << receiveNum << endl;
        if (receiveNum == -1)
        {
            //接收数据异常,关闭连接
            cout << "TCPServerManager::receiveRemote():: 1,接收数据异常,remote ip:" << remote << ",connfd:" << this->connfd << endl;
            this->remove(connfd);
            this->closeRemote(connfd);
            break;
        }
        else
        {
            cout << "TCPServerManager::receiveRemote():: 2,接收到,receiveNum:" << receiveNum << ",客户端说:" << receiveBuffer << endl;
            //输入并回复给客户端
            char sendBuf[MAX_DATA_SIZE];
            strncpy(sendBuf, receiveBuffer, receiveNum);

            // std::string message;
            // cin >> message;
            // fgets(sendBuf,MAX_DATA_SIZE,stdin);
            // strcpy(sendBuf, message.c_str()); // string 转换为char *
            std::cout << "服务端输入:" << sendBuf << endl;
            this->sendRemote(connfd, sendBuf);
        }
    }
    //接收数据异常,关闭连接
    cout << "TCPServerManager::receiveRemote():: 2,接收数据异常,remote ip:" << remote << ",connfd:" << this->connfd << endl;
    this->remove(connfd);
    this->closeRemote(connfd);
    // return true;
}

/**
 * @brief 发送消息给客户端
 *
 * @param connfd 客户端套接字
 * @param msg 消息
 * @return true
 * @return false
 */
bool TCPServerManager::sendRemote(int connfd, char *msg)
{
    cout << "TCPServerManager::sendRemote():: ..." << endl;
    int res = send(connfd, msg, MAX_DATA_SIZE, 0);
    cout << "TCPServerManager::sendRemote():: res:" << res << endl;
    if (res == -1)
    {
        return false;
    }
    return true;
}

/**
 * @brief 关闭与客户端套连接
 *
 * @param remotefd 客户端套接字描述符
 */
void TCPServerManager::closeRemote(int remotefd)
{
    cout << "TCPServerManager::closeRemote():: remotefd:" << remotefd << endl;
    close(remotefd);
}

/**
 * @brief 关闭服务端
 *
 */
void TCPServerManager::closeSelf()
{
    cout << "TCPServerManager::closeSelf():: ..." << endl;
    close(this->sockfd);
}

void TCPServerManager::add(int connfd, char *ip)
{
    auto iter = this->remotes->find(connfd);
    if (iter == this->remotes->end())
    {
        this->remotes->insert(std::pair<int, char *>(connfd, ip));
        cout << "TCPServerManager::add():: 保存connfd:" << connfd << ",IP:" << ip << ",到已连接列表" << endl;
    }
    else
    {
        cout << "TCPServerManager::add()::  connfd:" << connfd << ",IP:" << ip << ",已经保存到了已连接列表,不要再插入了 ..." << endl;
    }
}

void TCPServerManager::remove(int connfd)
{
    auto iter = this->remotes->find(connfd);
    if (iter != this->remotes->end())
    {
        char *ip = iter->second;
        this->remotes->erase(iter);
        cout << "TCPServerManager::remote():: 从已连接列表删除IP:" << ip << ",connfd:" << connfd << endl;
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
bool TCPServerManager::isConnect()
{
    int size = this->remotes->size();
    this->iSconneted = size > 0;
    cout << "TCPServerManager::isConnect():: size:" << size << ",connet:" << this->iSconneted << endl;
    return this->iSconneted;
}