#include "./include/Sample.h"

/**
 * @brief 获取系统当前日期,并将其保存到文件中
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    const char *pathname = "./file/current_time.txt"; //文件名
    int fd;                                           //文件描述符
    time_t t1;                                        //当前系统日期
    char *t2;                                         //当前系统时间字符串形式
    struct tm *t3;                                    //当前系统时间的结构体形式

    t1 = time(NULL); //获取当前系统时间
    t2 = ctime(&t1); //转化为当前系统时间字符串形式
    if (t2 == nullptr)
    {
        perror("ctime error");
        exit(1);
    }
    printf("当前系统时间:%s\n", t2);

    t3 = localtime(&t1); //转化为当前系统时间的结构体形式
    if (t3 == nullptr)
    {
        perror("localtime error");
        exit(2);
    }

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

    //使用strftime()函数格式化当前系统时间
    const char *format = "%Y-%m-%d %H:%M:%S 星期%w 第%W周";
    char datetime[MAX_BUFFER_SIZE];    //时间字符串缓冲区
    bzero(datetime, sizeof(datetime)); //清空缓冲区
    if (strftime(datetime, sizeof(datetime), format, t3) == 0)
    {
        perror("strftime error");
        exit(3);
    }
    fputs(datetime, stdout); //输出字符串

    //创建并打开文件,如果存在则置空
    if ((fd = open(pathname, O_RDWR | O_CREAT | O_TRUNC, 0644)) == -1)
    {
        perror("open error");
        exit(4);
    }
    //向文件中写入数据
    int nBytes = write(fd, datetime, strlen(datetime));
    if (nBytes == -1)
    {
        perror("write error");
        exit(5);
    }
    close(fd); //关闭文件描述符
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