#ifndef IHANDLE_THREAD_H
#define IHANDLE_THREAD_H

/**
 * @brief 抽象线程处理类
 *
 */
class IHandleThread
{
public:
    virtual ~IHandleThread() = default;
    virtual void start(int connfd, struct sockaddr_in client) = 0;
};

#endif