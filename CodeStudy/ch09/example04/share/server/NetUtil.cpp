#include "../../include/server/NetUtil.h"

NetUtil::NetUtil()
{
    cout << "NetUtil()构造函数" << endl;
}

NetUtil::~NetUtil()
{
    cout << "~NetUtil()析构函数" << endl;
}

/**
 * @brief 获取本机的IP地址信息字符串形式
 *
 * @return char*
 */
char *NetUtil::getIP()
{
    int size = 20;
    char *iplist[size];      //定义一个字符串二维数组,申请地址空间(很重要)
    memset(iplist, 0, size); //清空容器
    for (int i = 0; i < size; i++)
    {
        iplist[i] = (char *)malloc(sizeof(char *));
    }
    printf("%s\n", iplist[0]);
    int count = getIp(iplist, size); //获取IP地址
    printf("NetUtil::getIP():: IP地址列表个数:%d\n", count);
    if (count > 0)
    {
        char *ip = iplist[0]; //获取第一个IP地址
        printf("NetUtil::getIP():: IP:%s\n", ip);
        return ip;
    }
    return nullptr;
}

/**
 * @brief 获取IP地址的点分十进制字符串形式
 *
 * @param ipList IP地址列表
 * @param size  列表最大个数
 * @return int 返回有效IP地址列表个数
 */
int NetUtil::getIp(char **ipList, int size)
{
    printf("getIp():: ...\n");
    char computer[256];                            //本地主机名
    int ret;                                       //获取本地主机名结果
    struct hostent *hp;                            //保存IP地址信息的结构体
    ret = gethostname(computer, sizeof(computer)); //获取本地主机名称
    int count = 0;                                 //有效IP地址个数
    if (ret == -1)
    {
        perror("getIp():: 获取本地主机名错误");
    }
    else if (ret == 0)
    {
        printf("getIp():: 获取本地主机名成功:%s\n", computer);
        hp = gethostbyname(computer); //将本地主机名转换为IP地址
        if (hp == nullptr)
        {
            printf("getIp():: 主机名称为:%s,的主机信息没有被找到\n", computer);
        }
        else
        {
            //遍历结构体属性,获取主机的IP地址等信息
            char **p;                                     //主机的IP地址
            for (p = hp->h_addr_list; *p != nullptr; p++) //遍历主机的IP地址列表
            {
                struct in_addr in;                         //保存IP地址信息的in_addr结构体
                memcpy(&in.s_addr, *p, sizeof(in.s_addr)); //拷贝IP地址信息到结构体in_addr中
                char *ip = inet_ntoa(in);                  //将整数的IP地址转换为点分十进制字符串形式的IP地址
                char *hostName = hp->h_name;               //主机的正式名称
                strcpy(ipList[count], ip);                 //对字符串数组从新赋值
                printf("getIp():: 正式主机名:%s,IP:%s,", hostName, ip);
                printf("ipList[%d]:%s ,", count, ipList[count]);
                char **q; //主机的别名
                printf("别名:");
                for (q = hp->h_aliases; *q != nullptr; q++)
                {
                    printf(" %s", *q);
                }
                putchar('\n');
                count++;
            }
        }
    }
    return count;
}