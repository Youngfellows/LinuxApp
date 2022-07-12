#ifndef HOST_NAME_TRANSLATION_H
#define HOST_NAME_TRANSLATION_H

#include "../Global.h"
#include <unistd.h>
#include <sys/utsname.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netdb.h>

/**
 * @brief IP地址与主机名
 *
 */
class HostnameTranslation
{
private:
    char hostnameBuf[30]; //主机名
    char ipBuf[40];       // IP地址

public:
    HostnameTranslation();
    ~HostnameTranslation();
    char *getHostName();
    void getHostInfo();
    char *translateIP(char *hostname);
    void translateHostname(char *ip);
};
#endif