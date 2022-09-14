#include "./include/Sample.h"

/**
 * @brief 1. 调用abort函数发送SIGABRT信号使程序异常终止
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    if (signal(SIGABRT, signalHandler) == SIG_ERR)
    {
        printf("注册信号SIGABRT的信号处理函数错误\n");
        exit(1); //结束进程
    }
    abort(); //使程序异常终止
    printf("程序异常终止了,这句不会打印 ...\n");
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
    case SIGABRT:
        printf("捕捉到信号: SIGABRT ...\n");
        break;
    default:
        printf("捕捉到其他信号: %d\n", sig);
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