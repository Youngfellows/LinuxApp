#include "./include/Sample.h"

/**
 * @brief 更新系统时间
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    time_t t1;     //当前系统时间
    char *t2;      //当前系统时间字符串形式
    struct tm *t3; //当前系统时间结构体形式

    t1 = time(nullptr); //获取当前系统时间
    t2 = ctime(&t1);    //获取当前系统时间字符串形式
    cout << "t2=" << t2 << endl;

    t3 = localtime(&t1); //获取当前系统时间结构体形式

    //字符串拼接
    int year = t3->tm_year + 1900;
    int month = t3->tm_mon + 1;
    int day = t3->tm_mday;
    int hour = t3->tm_hour;
    int minute = t3->tm_min;
    int second = t3->tm_sec;
    int week = t3->tm_wday;
    std::string dateTime = to_string(year) + "年" + to_string(month) + "月" + to_string(day) + "日 " + to_string(hour) + ":" + to_string(minute) + ":" + to_string(second) + " 星期" + to_string(week);
    cout << "dateTime=" << dateTime << endl;

    std::ostringstream oss;
    oss << year << "年" << month << "月" << day << "日 " << hour << ":" << minute << ":" << second << " 星期" << week;
    dateTime = oss.str();
    cout << "dateTime2=" << dateTime << endl;

    //设置系统内核时间
    t3->tm_year = 2035 - 1900;
    t3->tm_mon = 3;
    t3->tm_mday = 23;
    t3->tm_hour = 9;
    t3->tm_min = 45;
    t3->tm_sec = 33;

    t1 = mktime(t3); //将struct tm类型时间转化为time_t 类型时间
    //stime(&t1);      //更新内核时间

    t2 = ctime(&t1); //获取当前系统时间字符串形式
    cout << "t2=" << t2 << endl;
    cout << endl;
}

void test2(int argc, char *argv[])
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