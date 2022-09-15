#include "./include/Sample.h"

/**
 * @brief 1. sleep()函数经过second秒,sleep函数返回0
 * @brief 2. sleep()函数捕捉到一个信号,并从信号处理函数返回,此时sleep返回剩余的秒数
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    int rtn;
    // if (signal(SIGQUIT, signalHandler) != SIG_ERR) //注册信号处理函数
    if (signal(SIGINT, signalHandler) != SIG_ERR) //注册信号处理函数
    {
        printf("请按下Ctrl + C\n");
        rtn = sleep(1000); //休眠1000秒,或者接受到SIGQUIT信号返回
        printf("sleep函数返回了,剩余秒数是:%d\n", rtn);
        rtn = sleep(3);
        printf("sleep函数执行完成了,剩余秒数:%d\n", rtn);
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
    printf("signalHandler being ...\n");
    switch (sig)
    {
    case SIGQUIT:
        printf("捕捉到信号: SIGINT\n");
        break;
    case SIGINT:
        printf("捕捉到信号: SIGQUIT\n");
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