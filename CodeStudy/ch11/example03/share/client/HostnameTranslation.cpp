#include "../../include/client/HostnameTranslation.h"

HostnameTranslation::HostnameTranslation()
{
    cout << "HostnameTranslation()构造函数" << endl;
}

HostnameTranslation::~HostnameTranslation()
{
    cout << "~HostnameTranslation()析构函数" << endl;
}

/**
 * @brief 获取本地主机名
 *
 */
char *HostnameTranslation::getHostName()
{
    cout << "HostnameTranslation::getHostName():: ..." << endl;
    char buf[30]; //保存获取的主机名
    int res = gethostname(buf, sizeof(buf) - 1);
    cout << "res:" << res << endl;
    if (res == 0)
    {
        //获取主机名成功
        cout << "hostname: " << buf << endl;
    }
    else if (res == -1)
    {
        //获取主机名失败
        cout << "获取主机名失败" << endl;
    }
    strcpy(hostnameBuf, buf);
    cout << "hostnameBuf:" << hostnameBuf << endl;
    return hostnameBuf;
}

/**
 * @brief 获取主机信息
 *
 */
void HostnameTranslation::getHostInfo()
{
    cout << "HostnameTranslation::getHostInfo():: ..." << endl;
    char computer[256];                                    //保存获取的主机名
    struct utsname uts;                                    //主机信息结构体
    int res = gethostname(computer, sizeof(computer) - 1); //获取主机名
    int res2 = uname(&uts);                                //获取主机信息
    cout << "res:" << res << ",res2:" << res2 << endl;
    if ((res != 0) || (res2 < 0))
    {
        cout << "获取主机信息失败" << endl;
    }
    else
    {
        cout << "主机名:" << computer << endl;
        cout << "系  统:" << uts.sysname << endl;
        cout << "硬  件:" << uts.machine << endl;
        cout << "节  点:" << uts.nodename << endl;
        cout << "版  本:" << uts.release << " " << uts.version << endl;
    }
}

/**
 * @brief 主机名转化为IP地址
 *
 */
char *HostnameTranslation::translateIP(char *hostname)
{
    cout << "HostnameTranslation::translateIP():: hostname:" << hostname << endl;
    struct hostent *hp;
    hp = gethostbyname(hostname); //主机名转化为IP地址,返回hostent结构体指针变量中
    if (hp != nullptr)
    {
        //获取IP地址列表
        char **p;
        for (p = hp->h_addr_list; *p != 0; p++)
        {
            struct in_addr in;
            char **q; //别名列表
            memcpy(&in.s_addr, *p, sizeof(in.s_addr));
            char *ip = inet_ntoa(in);          // IP地址
            memcpy(ipBuf, ip, sizeof(ip) + 1); //拷贝IP地址到全局变量
            char *hname = hp->h_name;          //主机的正式名称
            cout << "IP:" << ip << ",hname:" << hname << endl;
            //获取主机的别名列表
            for (q = hp->h_aliases; *q != 0; q++)
            {
                cout << "alias:" << *q << endl;
            }
        }
    }
    else
    {
        cout << "主机名转化为IP地址失败" << endl;
    }
    return ipBuf;
}

/**
 * @brief IP地址转化为主机名
 *
 */
void HostnameTranslation::translateHostname(char *ip)
{
    cout << "HostnameTranslation::translateHostname():: IP:" << ip << endl;
    in_addr_t addr;       //整数形式IP地址
    addr = inet_addr(ip); //将点分形式IP地址转化为整数形式
    cout << "addr:" << addr << endl;
    if (addr != -1)
    {
        //有效
        struct hostent *hp; //指向hostent结构体的指针
        hp = gethostbyaddr((char *)&addr, sizeof(addr), AF_INET);
        if (hp != nullptr)
        {
            //获取IP地址列表
            char **p;
            for (p = hp->h_addr_list; *p != 0; p++)
            {
                struct in_addr in;
                char **q; //别名列表
                memcpy(&in.s_addr, *p, sizeof(in.s_addr));
                char *ip = inet_ntoa(in); // IP地址
                // memcpy(ipBuf, ip, sizeof(ip) + 1); //拷贝IP地址到全局变量
                char *hname = hp->h_name; //主机的正式名称
                cout << "IP:" << ip << ",hname:" << hname << endl;
                //获取主机的别名列表
                for (q = hp->h_aliases; *q != 0; q++)
                {
                    cout << "alias:" << *q << endl;
                }
            }
        }
        else
        {
            cout << "IP地址转化为主机名失败" << endl;
        }
    }
}