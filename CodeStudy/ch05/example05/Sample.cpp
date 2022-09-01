#include "./include/Sample.h"

/**
 * @brief 让线程暂停5秒
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    cout << "倒计时开始:" << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << i << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1)); //暂停1秒钟
    }
    cout << "倒计时结束:" << endl;
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