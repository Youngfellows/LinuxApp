#include "./include/Sample.h"

/**
 * @brief 把可连接线程转化为分离线程
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    char *name = "周芷若";
    int age = 18;
    double salary = 26000;
    cout << "线程创建前: salary=" << salary << endl;
    std::thread myThread(threadFunction, name, age, &salary); //定义线程对象
    myThread.detach();                                        //分离线程

    cout << "线程分离后: salary=" << salary << endl;
    pthread_exit(nullptr); // main线程结束,进程并没有结束,下面的不会执行
    cout << "主线程结束了,这句不会被执行 ..." << endl;
    cout << endl;
}

/**
 * @brief 线程回调函数
 *
 * @param name 姓名
 * @param age 年龄
 * @param salary 工资
 */
void threadFunction(char *name, int age, double *salary)
{
    cout << "姓名:" << name << endl;
    cout << "年龄:" << age << endl;
    cout << "1,工资:" << *salary << endl;
    *salary += 3333;
    cout << "2,工资:" << *salary << endl;
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