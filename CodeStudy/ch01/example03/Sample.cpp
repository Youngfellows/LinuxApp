#include "./include/Sample.h"

/**
 * @brief 获取命令行参数
 *
 * @brief 测试: ./obj/test_sample.out
 * @brief 测试:
 * @brief 测试:
 * @brief 测试:
 * @brief 测试:
 * @brief 测试:
 * @brief 测试:
 * @brief 测试:
 *
 * @param arg 参数个数
 * @param args 参数列表
 */
void test1(int arg, char *args[])
{
    cout << "test1():: ..." << endl;
    printArgv(arg, args);
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

/**
 * @brief 打印命令行参数
 *
 * @param argc 参数个数
 * @param argv 参数列表
 */
void printArgv(int argc, char **argv)
{
    for (int i = 0; i < argc; i++)
    {
        char *param = argv[i];
        cout << "argv[" << i << "]=" << param << endl;
    }
}