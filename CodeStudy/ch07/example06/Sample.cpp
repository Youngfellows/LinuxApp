#include "./include/Sample.h"

/**
 * @brief 1. 通过signal调用改变SIGINT的响应方式
 * @brief 2. 程序运行过程中，按下Ctrl + C向进程发送SIGINT信号
 */
void test1()
{
    cout << "test1():: ..." << endl;
    int second = 0;
    //注册信号处理函数
    if (signal(SIGINT, signalHandler) != SIG_ERR)
    {
        while (true)
        {
            printf("%d\n", second++);
            sleep(1);
        }
    }

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
    case SIGINT:
        printf("捕捉到信号: SIGINT\n");
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