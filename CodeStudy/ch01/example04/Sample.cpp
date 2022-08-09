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

/**
 * @brief 获取和设置环境变量
 *
 */
void test2()
{
    cout << "test2():: ..." << endl;
    char *val = nullptr;
    val = getenv("USER"); //获取环境变量
    cout << "USER1=" << val << endl;

    setenv("USER", "lili", 1); //改变或者添加一个环境变量
    val = getenv("USER");      //获取环境变量
    cout << "USER2=" << val << endl;

    putenv("AGE=20"); //改变或者添加一个环境变量
    val = getenv("AGE");
    cout << "AGE1=" << val << endl;

    unsetenv("AGE"); //删除环境变量
    val = getenv("AGE");
    if (val != nullptr)
    {
        cout << "AGE2=" << val << endl;
    }
    else
    {
        cout << "val is null" << endl;
    }

    cout << endl;
}

/**
 * @brief 获取系统当前时间
 *
 */
void test3()
{
    cout << "test3():: ..." << endl;
    time_t nowtime;      //当前时间
    char *nowtime2;      //当前时间字符串形式
    struct tm *nowtime3; //当前时间,结构体形式

    time(&nowtime);             //获取系统当前时间
    nowtime2 = ctime(&nowtime); //获取当前时间字符串形式
    cout << "nowtime2=" << nowtime2 << endl;

    nowtime3 = localtime(&nowtime); //获取当前时间,结构体形式
    //字符串拼接
    int year = nowtime3->tm_year + 1900;
    int month = nowtime3->tm_mon + 1;
    int day = nowtime3->tm_mday;
    int hour = nowtime3->tm_hour;
    int minute = nowtime3->tm_min;
    int second = nowtime3->tm_sec;
    int week = nowtime3->tm_wday;
    std::string dateTime = to_string(year) + "年" + to_string(month) + "月" + to_string(day) + "日 " + to_string(hour) + ":" + to_string(minute) + ":" + to_string(second) + " 星期" + to_string(week);
    cout << "dateTime=" << dateTime << endl;

    std::ostringstream oss;
    oss << year << "年" << month << "月" << day << "日 " << hour << ":" << minute << ":" << second << " 星期" << week;
    dateTime = oss.str();
    cout << "dateTime2=" << dateTime << endl;

    cout << endl;
}

void test4()
{
    cout << "test4():: ..." << endl;
    cout << endl;
}