#ifndef REMOTE_INFO_H
#define REMOTE_INFO_H

/**
 * @brief 已经连接的客户端信息
 *
 */
typedef struct
{
    int connfd;   //客户端套接字描述符
    char ip[100]; //客户端远程地址
} RemoteInfo;

#endif