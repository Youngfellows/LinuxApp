#include "./include/Sample.h"

/**
 * @brief 1. 子进程向父进程发送SIGUSR1信号
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    pid_t pid; //进程ID
    //注册信号处理函数
    if (signal(SIGUSR1, signalHandler) == SIG_ERR)
    {
        printf("注册信号SIGUSR1的信号处理函数\n");
        exit(1); //结束进程
    }
    pid = fork(); //创建子进程
    if (pid == 0)
    {
        //子进程向父进程发送信号
        if (kill(getppid(), SIGUSR1) == -1)
        {
            printf("子进程向父进程发送信号失败\n");
            exit(2);
        }
    }
    else if (pid > 0)
    {
        wait(NULL); //父进程等待子进程结束
    }

    cout << endl;
}

/**
 * @brief 信号处理回调函数
 *
 * @param sig 信号量
 */
void signalHandler(int sig)
{
    printf("signalHandler begin ...\n");
    switch (sig)
    {
    case SIGUSR1:
        printf("捕捉到信号: SIGUSR1\n");
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