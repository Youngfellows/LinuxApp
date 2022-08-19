#include "./include/Sample.h"

/**
 * @brief 在子进程加载一个应用程序,父进程等待子进程执行完成
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    char *const args[] = {"ps", "-A", nullptr};
    pid_t pid;    //进程PID
    pid_t cpid;   //结束的子进程pid
    pid = fork(); //创建子进程
    if (pid == -1)
    {
        perror("fork error");
    }
    else if (pid == 0)
    {
        printf("子进程pid=%d\n", getpid());
        execvp(*args, args); //在子进程加载一个应用程序
        printf("加载应用程序错误\n");
        exit(0); //结束子进程
    }
    else
    {
        printf("父进程pid=%d\n", getpid());
        cpid = wait(NULL); //等待子进程结束
        printf("父进程pid=%d,pid=%d的子进程结束了\n", getpid(), cpid);
    }
    printf("进程pid=%d,执行了....\n", getpid());
    exit(0);
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