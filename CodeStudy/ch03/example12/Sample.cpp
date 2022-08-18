#include "./include/Sample.h"

/**
 * @brief 孤儿进程产生的原因: 父进程退出后,子进程仍然运行
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
        printf("子进程,pid=%d,ppid=%d\n", getpid(), getppid());
        sleep(3);
        printf("子进程,pid=%d,ppid=%d\n", getpid(), getppid());
    }
    else
    {
        printf("父亲程,pid=%d\n", getpid());
        exit(0);
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