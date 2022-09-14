#include "./include/Sample.h"

/**
 * @brief 1. 0值信号的特殊用法,检查pid进程是否存在
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    pid_t pid; //进程ID
    int ret;
    pid = fork(); //创建子进程
    if (pid == 0)
    {
        //子进程退出
        printf("子进程PID:%d,退出\n", getpid());
        exit(1);
    }
    else if (pid > 0)
    {
        printf("父进程PID:%d,子进程PID:%d\n", getpid(), pid);
        wait(NULL);         //父进程等待子进程结束
        ret = kill(pid, 0); //检查pid的进程是否存在
        if (ret == -1)
        {
            if (errno == ESRCH)
            {
                printf("子进程PID:%d,不存在\n", pid);
            }
        }
    }
    cout << endl;
}

/**
 * @brief 信号处理回调函数
 *
 * @param sig 信号
 */
void signalHandler(int sig)
{
    printf("signalHandler begin ...\n");
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