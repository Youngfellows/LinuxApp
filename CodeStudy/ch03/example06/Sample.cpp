#include "./include/Sample.h"

/**
 * @brief exec*系列函数,加载另外一个程序
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    //加载ps命令
    execlp("ps", "ps", "-o", "pid,ppid,pgrp,session,tpgid,comm", NULL);
    perror("exec ps");
    cout << endl;
    exit(1);
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