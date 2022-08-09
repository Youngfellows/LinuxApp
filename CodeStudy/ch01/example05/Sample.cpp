#include "./include/Sample.h"

/**
 * @brief 把参数或者时间设置成环境变量
 * @brief 测试:  ./obj/test_sample.out  USER
 * @brief 测试:  ./obj/test_sample.out  AGE
 * @brief 测试:  ./obj/test_sample.out  AGE 33
 *
 * @param arg 命令行参数格式
 * @param args 命令行参数列表
 */
void test1(int arg, char *args[])
{
    cout << "test1():: ..." << endl;
    time_t t1;   //当前系统时间
    char *t2;    //当前系统时间的字符串形式
    if (arg < 2) //命令行参数小于2
    {
        cout << "命令行参数不能小于2" << endl;
        return;
    }
    char *envName = args[1];
    char *env = getenv(envName);
    if (env != nullptr)
    {
        cout << "设置前:" << envName << "=" << env << endl;
    }
    else
    {
        cout << "设置前:" << envName << "=nullptr" << endl;
    }

    //刚好有两个命令行参数,当前时间设置成环境变量
    if (arg == 2)
    {
        t1 = time(nullptr);     //获取当前系统时间
        t2 = ctime(&t1);        //获取当前系统时间的字符串表现形式
        setenv(envName, t2, 1); //设置环境变量
    }
    else
    {
        env = args[2]; //第3个参数作为环境变量
        setenv(envName, env, 1);
    }

    env = getenv(envName); //获取环境变量
    if (env != nullptr)
    {
        cout << "设置后:" << envName << "=" << env << endl;
    }
    else
    {
        cout << "设置后:" << envName << "=nullptr" << endl;
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