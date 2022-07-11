#include "../../include/server/NetTcpServer.h"

NetTcpServer::NetTcpServer()
{
    cout << "NetTcpServer()构造函数" << endl;
    this->remotes = std::make_shared<std::map<char *, bool>>();
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
    this->my_addr.sin_family = AF_INET;                         //协议族
    this->my_addr.sin_port = htons(SERVER_PORT);                //端口
    this->my_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // IP地址
    // this->my_addr.sin_addr.s_addr = htonl(INADDR_ANY); // IP地址
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
 * @brief 等待客户端连接,如果有新的客户端连接,则产生新的连接套接字
 *
 * @return true
 * @return false
 */
void NetTcpServer::acceptRemote()
{
    /**
    //等待客户端连接，如果有客户端连接，则产生新的连接套接字
    int sin_size = sizeof(struct sockaddr_in);
    if ((client_fd = accept(sockfd, (struct sockaddr *)&remote_addr, &sin_size)) == -1)
    {
        perror("accept");
        exit(1);
    }
     *
     */
    while (true)
    {
        //开启多线程处理每一个远程客户端连接
        socklen_t sin_size = sizeof(struct sockaddr_in);
        this->connfd = accept(this->sockfd, (struct sockaddr *)&remote_addr, &sin_size);
        char *remote = inet_ntoa(remote_addr.sin_addr);
        // cout << "NetTcpServer::acceptRemote():: remote ip:" << remote << ",connfd:" << this->connfd << endl;
        if (this->connfd == -1)
        {
            //连接断开或者异常
            // cout << "服务端与远程客户端" << remote << "断开链接" << endl;
            this->remove(remote);
        }
        else
        {
            //加如到已经连接容器列表中
            cout << "服务端与远程客户端" << remote << "建立链接成功 ..." << endl;
            this->add(remote);
        }
    }
    // return true;
}

void NetTcpServer::add(char *ip)
{
    auto iter = this->remotes->find(ip);
    if (iter == this->remotes->end())
    {
        this->remotes->insert(std::pair<char *, bool>(ip, true));
        cout << "NetTcpServer::add():: 保存IP:" << ip << ",到已连接列表" << endl;
    }
    else
    {
        cout << "NetTcpServer::add():: IP:" << ip << ",已经保存到了已连接列表,不要再插入了 ..." << endl;
    }
}

void NetTcpServer::remove(char *ip)
{
    auto iter = this->remotes->find(ip);
    if (iter != this->remotes->end())
    {
        this->remotes->erase(iter);
        cout << "NetTcpServer::remote():: 从已连接列表删除IP:" << ip << endl;
    }
    else
    {
        // cout << "NetTcpServer::remote():: 已连接列表不存在IP:" << ip << ",无需要删除" << endl;
    }
}

bool NetTcpServer::receive()
{
    return true;
}

bool NetTcpServer::sendToRemote()
{
    return true;
}

void NetTcpServer::closeRemote(int remotefd)
{
}

void NetTcpServer::close()
{
}