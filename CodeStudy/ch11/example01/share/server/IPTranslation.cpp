#include "../../include/server/IPTranslation.h"

IPTranslation::IPTranslation()
{
    cout << "IPTranslation()构造函数" << endl;
}

IPTranslation::~IPTranslation()
{
    cout << "~IPTranslation()析构函数" << endl;
}

/**
 * @brief IP地址点分十进制形式转化为整数形式
 * @brief 32位的网络字节序,255.255.255.255无效
 */
void IPTranslation::translation1()
{
    cout << "IPTranslation::translation1():: ..." << endl;
    char buf[20] = "192.168.2.36";
    cout << "buf: " << buf << endl;
    in_addr_t ip = inet_addr(buf);
    cout << "IP:" << ip << endl;
}

/**
 * @brief IP地址点分十进制形式转化为整数形式
 * @brief 32位的主机字节序,255.255.255.255无效
 */
void IPTranslation::translation2()
{
    cout << "IPTranslation::translation2():: ..." << endl;
    char buf[20] = "192.168.2.133";
    cout << "buf:" << buf << endl;
    in_addr_t ip = inet_network(buf);
    cout << "IP:" << ip << endl;
}

/**
 * @brief IP地址点分十进制形式转化为整数形式
 * @brief 32位的网络字节序,255.255.255.255有效
 */
void IPTranslation::translation3()
{
    cout << "IPTranslation::translation3():: ..." << endl;
    const char *buf = "192.168.4.172";
    // char buf[20] = "192.168.2.133";
    cout << "buf:" << buf << endl;
    struct sockaddr_in myaddy;
    int ip = inet_aton(buf, &(myaddy.sin_addr));
    cout << "ip:" << ip << endl;
}

/**
 * @brief 整数形式IP地址转化为点分十进制形式
 * @brief
 */
void IPTranslation::translation4()
{
    cout << "IPTranslation::translation4():: ..." << endl;
    const char *buf = "192.168.4.172";
    cout << "buf:" << buf << endl;
    struct sockaddr_in myaddr;
    int ip = inet_aton(buf, &(myaddr.sin_addr));
    cout << "ip:" << ip << endl;
    char *ipAddress = inet_ntoa(myaddr.sin_addr);
    cout << "ipAddress:" << ipAddress << endl;
}