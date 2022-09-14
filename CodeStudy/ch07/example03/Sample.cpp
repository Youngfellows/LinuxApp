#include "./include/Sample.h"

/**
 * @brief 1. 向进程自己发送信号
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    //注册信号处理函数
    if (signal(SIGUSR1, signalHandler) == SIG_ERR)
    {
        printf("注册信号SIGUSR1的信号处理函数错误\n");
        exit(1);
    }
    raise(SIGUSR1); //向进程自己发送信号
    cout << endl;
}

/**
 * @brief 信号处理函数
 *
 * @param sig 信号
 */
void signalHandler(int sig)
{
    printf("signalHandler begin ...\n");
    switch (sig)
    {
    case SIGUSR1:
        printf("信号SIGUSR1被捕捉到了\n");
        break;
    default:
        printf("其他信号%d,被捕捉到了\n", sig);
        break;
    }
}

void test2()
{
    cout << "test2():: ..." << endl;
    cout << endl;
}

void test3()
{
    cout << "test3():: ..." << endl;
    cout << endl;
}

void test4()
{
    cout << "test4():: ..." << endl;
    cout << endl;
}