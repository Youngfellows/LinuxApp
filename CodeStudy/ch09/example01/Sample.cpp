#include "./include/Sample.h"

/**
 * @brief 1. IP地址形式转换
 * @brief 2. 将IP地址从点分十进制形式的字符串转换为32位整型形式,网络字节序
 */
void test1()
{
    cout << "test1():: ..." << endl;
    const char *ip = "192.168.10.24"; // IP地址字符串
    in_addr_t addr;                   //网络字节序
    addr = inet_addr(ip);             //将IP地址从点分十进制形式的字符串转换为32位整型形式,网络字节序
    if (addr == -1)
    {
        printf("获取IP:%s,的网络字节序错误\n", ip);
    }
    else
    {
        printf("获取IP:%s,的网络字节序成功,addr:%d\n", ip, addr);
    }

    cout << endl;
}

/**
 * @brief 1. IP地址形式转换
 * @brief 2. 将IP地址从点分十进制形式的字符串转换为32位整型形式,网络字节序
 * @brief 3. 255.255.255.255 认为是无效的
 */
void test2()
{
    cout << "test2():: ..." << endl;
    const char *ip = "255.255.255.255"; // IP地址字符串
    in_addr_t addr;                     //网络字节序
    addr = inet_addr(ip);               //将IP地址从点分十进制形式的字符串转换为32位整型形式,网络字节序
    if (addr == -1)
    {
        printf("获取IP:%s,的网络字节序错误\n", ip);
    }
    else
    {
        printf("获取IP:%s,的网络字节序成功,addr:%d\n", ip, addr);
    }

    cout << endl;
}

/**
 * @brief 1. IP地址形式转换
 * @brief 2. 将IP地址从点分十进制形式的字符串转换为32位整型形式,主机字节序
 * @brief 3. 255.255.255.255 认为是无效的
 */
void test3()
{
    cout << "test3():: ..." << endl;
    const char *ip = "192.168.10.24"; // IP地址字符串
    in_addr_t addr;                   //网络字节序
    addr = inet_network(ip);          //将IP地址从点分十进制形式的字符串转换为32位整型形式,主机字字节序
    if (addr == -1)
    {
        printf("获取IP:%s,的主机字字节序错误\n", ip);
    }
    else
    {
        printf("获取IP:%s,的主机字字节序成功,addr:%d\n", ip, addr);
    }

    cout << endl;
}

/**
 * @brief 1. IP地址形式转换
 * @brief 2. 将IP地址从点分十进制形式的字符串转换为32位整型形式,主机字节序
 * @brief 3. 255.255.255.255 认为是无效的
 */
void test4()
{
    cout << "test4():: ..." << endl;
    const char *ip = "255.255.255.255"; // IP地址字符串
    in_addr_t addr;                     //网络字节序
    addr = inet_network(ip);            //将IP地址从点分十进制形式的字符串转换为32位整型形式,主机字字节序
    if (addr == -1)
    {
        printf("获取IP:%s,的主机字字节序错误\n", ip);
    }
    else
    {
        printf("获取IP:%s,的主机字字节序成功,addr:%d\n", ip, addr);
    }

    cout << endl;
}

/**
 * @brief 1. IP地址形式转换
 * @brief 2. 将IP地址从点分十进制形式的字符串转换为32位整型形式,网络字节序
 * @brief 3. 255.255.255.255 是有效的
 */
void test5()
{
    cout << "test5():: ..." << endl;
    const char *ip = "192.168.10.123";       // IP地址字符串
    struct sockaddr_in myaddr;               // IP地址一般在sockaddr_in中使用
    int ret;                                 //获取网络字节序结果
    ret = inet_aton(ip, &(myaddr.sin_addr)); //将IP地址从点分十进制形式的字符串转换为32位整型形式,网络字节序
    if (ret != 0)
    {
        printf("获取IP地址%s,的网络字节序成功,addr:%d\n", ip, myaddr.sin_addr);
    }
    else
    {
        printf("获取IP地址%s,的网络字节序成功\n", ip);
    }

    cout << endl;
}

/**
 * @brief 1. IP地址形式转换
 * @brief 2. 将IP地址从点分十进制形式的字符串转换为32位整型形式,网络字节序
 * @brief 3. 255.255.255.255 是有效的
 */
void test6()
{
    cout << "test6():: ..." << endl;
    const char *ip = "255.255.255.255";      // IP地址字符串
    struct sockaddr_in myaddr;               // IP地址一般在sockaddr_in中使用
    int ret;                                 //获取网络字节序结果
    ret = inet_aton(ip, &(myaddr.sin_addr)); //将IP地址从点分十进制形式的字符串转换为32位整型形式,网络字节序
    if (ret != 0)
    {
        printf("获取IP地址%s,的网络字节序成功,addr:%d\n", ip, myaddr.sin_addr);
    }
    else
    {
        printf("获取IP地址%s,的网络字节序成功\n", ip);
    }

    cout << endl;
}

/**
 * @brief 1. IP地址形式转换
 * @brief 2. 将IP地址从32位整型形式,网络字节序转换为点分十进制形式的字符串
 */
void test7()
{
    cout << "test7():: ..." << endl;
    const char *ip = "192.168.10.123";       // IP地址字符串
    struct sockaddr_in myaddr;               // IP地址一般在sockaddr_in中使用
    int ret;                                 //获取网络字节序结果
    ret = inet_aton(ip, &(myaddr.sin_addr)); //将IP地址从点分十进制形式的字符串转换为32位整型形式,网络字节序
    if (ret != 0)
    {
        printf("获取IP地址%s,的网络字节序成功,addr:%d\n", ip, myaddr.sin_addr);
    }
    else
    {
        printf("获取IP地址%s,的网络字节序成功\n", ip);
    }
    char *ipStr = inet_ntoa(myaddr.sin_addr); //将IP地址从32位整型形式,网络字节序转换为点分十进制形式的字符串
    printf("IP:%s\n", ipStr);
    cout << endl;
}

/**
 * @brief 1. IP地址形式转换
 * @brief 2. 将IP地址从32位整型形式,网络字节序转换为点分十进制形式的字符串
 */
void test8()
{
    cout << "test8():: ..." << endl;
    const char *ip = "255.255.255.255";      // IP地址字符串
    struct sockaddr_in myaddr;               // IP地址一般在sockaddr_in中使用
    int ret;                                 //获取网络字节序结果
    ret = inet_aton(ip, &(myaddr.sin_addr)); //将IP地址从点分十进制形式的字符串转换为32位整型形式,网络字节序
    if (ret != 0)
    {
        printf("获取IP地址%s,的网络字节序成功,addr:%d\n", ip, myaddr.sin_addr);
    }
    else
    {
        printf("获取IP地址%s,的网络字节序成功\n", ip);
    }
    char *ipStr = inet_ntoa(myaddr.sin_addr); //将IP地址从32位整型形式,网络字节序转换为点分十进制形式的字符串
    printf("IP:%s\n", ipStr);
    cout << endl;
}

/**
 * @brief 获取本地主机名称
 *
 */
void test9()
{
    cout << "test9():: ..." << endl;
    char hostNameBuf[100];                               //本地主机名称
    int ret;                                             //获取本地主机名的结果
    ret = gethostname(hostNameBuf, sizeof(hostNameBuf)); //获取本地主机名称
    if (ret == 0)
    {
        printf("本地主机名称:%s\n", hostNameBuf);
    }
    else if (ret == -1)
    {
        perror("gethostname failed");
        printf("获取本地主机名失败\n");
    }
    cout << endl;
}

/**
 * @brief 获取主机信息
 *
 */
void test10()
{
    cout << "test10():: ..." << endl;
    char computer[256];                             //本地主机名称
    struct utsname uts;                             //主机信息结构体
    int ret1;                                       //获取本地主机名称结果
    int ret2;                                       //获取主机信息结果
    ret1 = gethostname(computer, sizeof(computer)); //获取本地主机名称
    ret2 = uname(&uts);                             //获取主机信息
    if (ret1 != 0 || ret2 < 0)
    {
        fprintf(stderr, "不能够获取主机信息\n");
    }
    else
    {
        printf("计算机的主机名称是:%s\n", computer);
        printf("操作系统是:%s\n", uts.sysname);
        printf("计算机CPU系统架构是:%s\n", uts.machine);
        printf("计算机节点名:%s\n", uts.nodename);
        printf("系统版本是:%s %s\n", uts.release, uts.version);
    }

    cout << endl;
}

/**
 * @brief 本地主机名转化为IP地址
 *
 */
void test11()
{
    cout << "test11():: ..." << endl;
    char computer[256];                            //本地主机名
    int ret;                                       //获取本地主机名结果
    struct hostent *hp;                            //保存IP地址信息的结构体
    ret = gethostname(computer, sizeof(computer)); //获取本地主机名称
    if (ret == -1)
    {
        perror("获取本地主机名错误");
    }
    else if (ret == 0)
    {
        printf("获取本地主机名成功:%s\n", computer);
        hp = gethostbyname(computer); //将本地主机名转换为IP地址
        if (hp == nullptr)
        {
            printf("主机名称为:%s,的主机信息没有被找到\n", computer);
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
                printf("正式主机名:%s,IP:%s,", hostName, ip);
                char **q; //主机的别名
                printf("别名:");
                for (q = hp->h_aliases; *q != nullptr; q++)
                {
                    printf(" %s", *q);
                }
                putchar('\n');
            }
        }
    }
    cout << endl;
}

/**
 * @brief 将IP地址转换为主机名
 *
 */
void test12()
{
    cout << "test12():: ..." << endl;
    const int size = 20;
    char *iplist[size];      //定义一个字符串二维数组,申请地址空间(很重要)
    memset(iplist, 0, size); //清空容器
    for (int i = 0; i < size; i++)
    {
        iplist[i] = (char *)malloc(sizeof(char *));
    }
    printf("%s\n", iplist[0]);
    int count = getIp(iplist, size); //获取IP地址
    printf("IP地址列表个数:%d\n", count);
    if (count > 0)
    {
        char *ip = iplist[0]; //获取第一个IP地址
        printf("IP:%s\n", ip);

        // unsigned long addr; //网络字节序
        in_addr_t addr;     //网络字节序
        struct hostent *hp; //保存IP地址信息的结构体
        if (((int)(addr = inet_addr(ip))) == -1)
        {
            printf("转换为网络字节序错误\n");
        }
        else
        {
            hp = gethostbyaddr((char *)&addr, sizeof(addr), AF_INET); //将IP地址转换为主机名
            if (hp == nullptr)
            {
                printf("将IP地址转换为主机名错误\n");
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
                    printf("正式主机名:%s,IP:%s,", hostName, ip);
                    char **q; //主机的别名
                    printf("别名:");
                    for (q = hp->h_aliases; *q != nullptr; q++)
                    {
                        printf(" %s", *q);
                    }
                    putchar('\n');
                }
            }
        }
    }

    cout << endl;
}

/**
 * @brief 获取IP地址的点分十进制字符串形式
 *
 * @param ipList IP地址列表
 * @param size  列表最大个数
 * @return int 返回有效IP地址列表个数
 */
int getIp(char **ipList, int size)
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

void test13()
{
    cout << "test13():: ..." << endl;
    cout << endl;
}

void test14()
{
    cout << "test14():: ..." << endl;
    cout << endl;
}

void test15()
{
    cout << "test15():: ..." << endl;
    cout << endl;
}