#include "./include/Sample.h"

/**
 * @brief 使用system()函数执行shell命令
 * @brief date +"%Y-%m-%d %H:%M:%S 星期%w 第%W周"
 */
void test1()
{
    cout << "test1():: ..." << endl;
    system("date +\"%Y-%m-%d %H:%M:%S 星期%w 第%W周\">./file/datetime.txt");
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