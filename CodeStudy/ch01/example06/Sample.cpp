#include "./include/Sample.h"

void test1()
{
    cout << "test1():: ..." << endl;
    //获取错误码
    cout << "前: errno=" << errno << endl;
    //打开一个不存在的文件
    if (fopen("test111.txt", "r") == nullptr)
    {
        cout << "1打开文件错误: errno=" << errno << endl;
        char *err = strerror(errno); //输出错误信息
        cout << err << endl;
        //打印用户自定义的错误提示信息
        perror("fopen");
        cout << "2打开文件错误: errno=" << errno << endl;
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