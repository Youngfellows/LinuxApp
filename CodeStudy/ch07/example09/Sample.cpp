#include "./include/Sample.h"

/**
 * @brief 1. pause使进程挂起并等待接收某个信号
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    int rtn;
    if (signal(SIGALRM, signalHandler) != SIG_ERR)
    {
        rtn = alarm(5); //设置一个5秒的定时器
        printf("第1次返回,上一个定时器剩余时间:%d\n", rtn);
        sleep(2);       //休眠2秒
        rtn = alarm(5); //设置一个5秒的定时器
        printf("第2次返回,上一个定时器剩余时间:%d\n", rtn);
        rtn = pause(); //使进程挂起并接受一个SIGALRM信号
        printf("pause 函数返回了: %d\n", rtn);
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
    case SIGALRM:
        printf("捕捉到信号: SIGALRM\n");
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