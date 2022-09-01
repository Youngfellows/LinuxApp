#include "./include/Sample.h"

/**
 * @brief 暂停线程到下1分钟
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    using std::chrono::system_clock;
    std::time_t tt = system_clock::to_time_t(system_clock::now()); //获取系统当前时间
    struct std::tm *ptm = std::localtime(&tt);                     //获取当前时间的结构体形式
    getNowTime();                                                  //打印当前时间
    cout << "等待下一分钟开始 ..." << endl;
    ++ptm->tm_min;   //累加1分钟
    ptm->tm_sec = 0; //秒数置0
    //暂停执行到下一个整数分时间
    std::this_thread::sleep_until(system_clock::from_time_t(mktime(ptm))); //结构体时间转化为time时间
    getNowTime();                                                          //打印当前时间
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
 * @brief 获取并打印当前时间
 *
 */
void getNowTime()
{
    timespec time;
    struct tm nowTime; //时间结构体形式
    //获取相对于1970年到现在的秒数
    clock_gettime(CLOCK_REALTIME, &time);
    localtime_r(&time.tv_sec, &nowTime); //把时间转化为结构体形式
    // char current[1024];
    printf("%04d-%02d-%02d %02d:%02d:%02d\n",
           nowTime.tm_year + 1900,
           nowTime.tm_mon + 1,
           nowTime.tm_mday,
           nowTime.tm_hour,
           nowTime.tm_min,
           nowTime.tm_sec);
}