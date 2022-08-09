#include "./include/Sample.h"

void test1()
{
    cout << "test1():: ..." << endl;
    //遍历当前进程的环境变量
    extern char **environ;
    for (int i = 0; environ[i] != nullptr; i++)
    {
        char *env = environ[i];
        cout << "environ[" << i << "]=" << env << endl;
    }

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