#include "../../include/client/NetTcpClient.h"

NetTcpClient::NetTcpClient()
{
    cout << "NetTcpClient()构造函数" << endl;
}

NetTcpClient::~NetTcpClient()
{
    cout << "~NetTcpClient()析构函数" << endl;
}

/**
 * @brief 创建socket套接字
 *
 * @return true
 * @return false
 */
bool NetTcpClient::createSocket()
{
    this->sockdf = socket(AF_INET, SOCK_STREAM, 0);
    cout << "NetTcpClient::createSocket():: sockdf:" << this->sockdf << endl;
    if (this->sockdf == -1)
    {
        return false;
    }
    return true;
}

/**
 * @brief 向服务端发起连接
 *
 * @return true
 * @return false
 */
bool NetTcpClient::connectServer()
{
    // IP地址与主机名相互转化
    std::shared_ptr<HostnameTranslation> translation = std::make_shared<HostnameTranslation>();
    char *hostname = translation->getHostName();
    char *ip = translation->translateIP(hostname);
    cout << "NetTcpClient::connectServer():: 1,IP:" << ip << endl;
    // translation->translateHostname(ip);

    this->serverAddr.sin_family = AF_INET;          //协议族
    this->serverAddr.sin_port = htons(SERVER_PORT); //端口
    // this->serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // IP地址
    this->serverAddr.sin_addr.s_addr = inet_addr(ip); // IP地址
    // this->serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);      // IP地址
    bzero(&(this->serverAddr.sin_zero), 8); //填充0
    cout << "NetTcpClient::connectServer():: 2,IP:" << ip << endl;

    int connectRes = connect(this->sockdf, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr));
    cout << "NetTcpClient::connectServer():: connectRes:" << connectRes << endl;
    if (connectRes == -1)
    {
        this->isConnect = false; //连接失败
        return false;
    }
    this->isConnect = true; //连接成功
    return true;
}

/**
 * @brief 接收服务端消息
 *
 */
void NetTcpClient::receive()
{
    cout << "NetTcpClient::receive():: isConnect:" << isConnected() << endl;
    int receiveBytes = 0;           //接收到服务端数据大小
    char buffer[MAX_DATA_SIZE];     //接收数据缓冲区
    char sendBuffer[MAX_DATA_SIZE]; //发送数据缓冲区
    while (isConnected())
    {
        //接收到服务端数据
        receiveBytes = recv(this->sockdf, buffer, MAX_DATA_SIZE, 0);
        cout << "NetTcpClient::receive():: receiveBytes:" << receiveBytes << endl;
        if (receiveBytes == -1)
        {
            closeRemote();
            break;
        }
        cout << "服务端说:" << buffer << endl;

        //输入要回复的消息
        cout << "客户端输入:";
        std::string message;                 //回的消息
        std::cin >> message;                 //输入要回的消息
        strcpy(sendBuffer, message.c_str()); // string字符串转换为char *
        this->sendToRemote(sendBuffer);
    }
}

/**
 * @brief 发送到服务端
 *
 * @param message 要发送的消息
 * @return true
 * @return false
 */
bool NetTcpClient::sendToRemote(char *message)
{
    cout << "NetTcpClient::sendToRemote():: message:" << message << endl;
    int sendRes = send(this->sockdf, message, MAX_DATA_SIZE, 0);
    cout << "NetTcpClient::sendToRemote():: sendRes:" << sendRes << endl;
    if (sendRes == -1)
    {
        closeRemote();
        return false;
    }
    return true;
}

/**
 * @brief 关闭与服务端连接
 *
 */
void NetTcpClient::closeRemote()
{
    close(this->sockdf);     //关闭服务端套接字连接
    this->isConnect = false; //接收数据失败,连接断开
}

/**
 * @brief 是否与远程服务端连接上
 *
 * @return true
 * @return false
 */
bool NetTcpClient::isConnected()
{
    return this->isConnect;
}
