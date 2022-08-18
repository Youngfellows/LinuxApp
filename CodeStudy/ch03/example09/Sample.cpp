#include "./include/Sample.h"

/**
 * @brief exit()进程退出函数
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    char content[] = "今天是星期四,天气不错哦,适合出去玩...\n";
    //向标准输出文件中写入输入
    if (write(STDIN_FILENO, content, strlen(content)) < 0)
    {
        perror("write error");
    }
    //注册进程终止回调函数
    atexit(func1);
    atexit(func2);
    exit(0); //终止进程
    cout << endl;
}

void func1()
{
    cout << "func1():: 回调函数执行了 ..." << endl;
}

void func2()
{
    cout << "func2():: 回调函数执行了 ..." << endl;
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