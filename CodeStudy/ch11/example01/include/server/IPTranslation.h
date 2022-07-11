#ifndef IP_TRANSLATION_H
#define IP_TRANSLATION_H

#include "../Global.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/**
 * @brief 实体类: IP地址转化
 *
 */
class IPTranslation
{
private:
public:
    IPTranslation();
    ~IPTranslation();
    void translation1();
    void translation2();
    void translation3();
    void translation4();
};
#endif