#ifndef NET_UTIL_H
#define NET_UTIL_H

#include "../Global.h"

/**
 * @brief 获取本机IP地址工具类
 *
 */
class NetUtil
{
private:
public:
    NetUtil();
    ~NetUtil();
    static char *getIP();                      //获取本机的IP地址信息
    static int getIp(char **ipList, int size); //获取IP地址列表
};
#endif