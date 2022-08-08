#include "./include/Sample.h"

/**
 * @brief  获取命令行参数
 * @brief  测试: ./obj/test_sample.out  aa bb cc
 * @param arg
 * @param args
 */
void test1(int arg, char *args[])
{
    cout << "test1():: ..." << endl;
    cout << "test1():: arg:" << arg << endl;
    for (int i = 0; i < arg; i++)
    {
        // char *param = args[i];
        char *param = *(args + i);
        cout << "args[" << i << "]=" << param << endl;
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