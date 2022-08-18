#include "./include/Sample.h"

int global = 0; //定义全局变量

/**
 * @brief vfork创建的父子进程共享数据空间
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    int var = 0; //局部变量
    pid_t pid;   //进程PID
    printf("进程创建前\n");
    pid = vfork(); //创建子进程
    if (pid < 0)
    {
        perror("vfork error");
        // exit(0);
    }
    else if (pid == 0)
    {
        printf("子进程:%d\n", getpid());
        global++;
        var++;
        _exit(0); //结束子进程
    }
    else
    {
        printf("父进程:%d\n", getpid());
    }
    sleep(3); //休眠3秒
    printf("pid=%d,global=%d,var=%d\n", getpid(), global, var);
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