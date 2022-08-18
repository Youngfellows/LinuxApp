#include "./include/Sample.h"

/**
 * @brief 僵尸进程: 父进程结束前没有调用wait,已经终止运行的子进程没有完全销毁,处于僵尸状态
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    pid_t pid;    //进程pid
    pid = fork(); //创建子进程
    if (pid == -1)
    {
        perror("fork error");
    }
    else if (pid == 0)
    {
        printf("子进程pid=%d\n", getpid());
    }
    else
    {
        printf("父进程pid=%d\n", getpid());
        wait(NULL); //父进程调用wait,子进程结束时释放资源,避免成为僵尸进程
        while (1)
        {
        }
    }
    printf("%d进程执行了...\n", getpid());
    cout << endl;
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