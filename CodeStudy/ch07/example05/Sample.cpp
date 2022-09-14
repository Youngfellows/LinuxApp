#include "./include/Sample.h"

/**
 * @brief 1. 进程对SIGINT的默认响应方式是终止信号
 * @brief 2. 程序运行过程中，按下Ctrl + C中断进程
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    int second = 0;
    while (true)
    {
        printf("%d\n", second++);
        sleep(1);
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