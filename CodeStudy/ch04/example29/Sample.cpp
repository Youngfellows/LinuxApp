#include "./include/Sample.h"

void test1()
{
    cout << "test1():: ..." << endl;
    pid_t tid; //获取进程ID
    tid = syscall(SYS_gettid);
    printf("tid:%d\n", tid);
    tid = syscall(SYS_tgkill, getpid(), tid, SIGHUP); //挂起
    printf("tid:%d\n", tid);

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