#include "./include/Sample.h"

/**
 * @brief exec*系列函数,加载另外一个程序
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    char *args[] = {"ps", "-o", "pid,ppid,pgrp,session,tpgid,comm", NULL}; //参数字符串数组
    execvp(args[0], args);
    perror("execvp ps");
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