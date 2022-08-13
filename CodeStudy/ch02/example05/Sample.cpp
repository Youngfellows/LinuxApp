#include "./include/Sample.h"

/**
 * @brief 改变指定文件的所有者及所属组
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    //改变指定文件的所有者及所属组
    const char *pathname = "./file/f1.txt"; //文件名
    int rt = unlink(pathname);              //如果文件存在,则删除
    if (rt == -1)
    {
        perror("unlink error");
        cout << "删除文件失败:" << pathname << endl;
    }
    system("touch ./file/f1.txt"); //创建文件
    struct stat buf;               //系统文件属性
    stat(pathname, &buf);          //获取系统文件属性
    cout << "旧,用户ID:" << buf.st_uid << ",组ID:" << buf.st_gid << endl;

    chown(pathname, -1, 1001); //文件所有者不改,所属组改成1001
    stat(pathname, &buf);
    cout << "新,用户ID:" << buf.st_uid << ",组ID:" << buf.st_gid << endl;

    cout << endl;
}

/**
 * @brief 修改文件访问权限
 *
 */
void test2()
{
    cout << "test2():: ..." << endl;
    const char *pathname = "./file/f2.txt"; //文件名
    struct stat buf;                        //系统文件属性
    int rt = stat(pathname, &buf);          //获取系统文件属性
    if (rt == -1)
    {
        perror("stat error");
        cout << "获取系统文件属性失败:" << pathname << endl;
    }
    else
    {
        //获取文件访问权限
        cout << "更新权限前:" << endl;
        getMode(buf);
        cout << "=================================" << endl;
        chmod(pathname, 0600);
        rt = stat(pathname, &buf);
        cout << "更新权限后:" << endl;
        getMode(buf);
    }
    cout << endl;
}

/**
 * @brief 获取文件权限
 *
 * @param buf 系统文件属性
 */
void getMode(struct stat buf)
{
    //判断文件权限
    //用户权限
    if (buf.st_mode & S_IRUSR)
    {
        cout << "用户可读" << endl;
    }
    else
    {
        cout << "用户不可读" << endl;
    }

    if (buf.st_mode & S_IWUSR)
    {
        cout << "用户可写" << endl;
    }
    else
    {
        cout << "用户不可写" << endl;
    }

    if (buf.st_mode & S_IXUSR)
    {
        cout << "用户可执行" << endl;
    }
    else
    {
        cout << "用户不可执行" << endl;
    }

    //所属组权限
    if (buf.st_mode & S_IRGRP)
    {
        cout << "所属组可读" << endl;
    }
    else
    {
        cout << "所属组不可读" << endl;
    }

    if (buf.st_mode & S_IWGRP)
    {
        cout << "所属组可写" << endl;
    }
    else
    {
        cout << "所属组不可写" << endl;
    }

    if (buf.st_mode & S_IXGRP)
    {
        cout << "所属组可执行" << endl;
    }
    else
    {
        cout << "所属组不可执行" << endl;
    }

    //其他成员权限
    if (buf.st_mode & S_IROTH)
    {
        cout << "其他成员可读" << endl;
    }
    else
    {
        cout << "其他成员不可读" << endl;
    }

    if (buf.st_mode & S_IWOTH)
    {
        cout << "其他成员可写" << endl;
    }
    else
    {
        cout << "其他成员不可写" << endl;
    }

    if (buf.st_mode & S_IXOTH)
    {
        cout << "其他成员可执行" << endl;
    }
    else
    {
        cout << "其他成员不可执行" << endl;
    }
}

/**
 * @brief 改变文件时间
 *
 */
void test3()
{
    cout << "test3():: ..." << endl;
    const char *pathname = "./file/f2.txt"; //文件名
    struct stat buf;                        //系统文件属性
    int rt = stat(pathname, &buf);          //获取系统文件属性
    if (rt == -1)
    {
        perror("stat error");
        cout << "获取系统文件属性失败:" << pathname << endl;
    }
    else
    {
        time_t stAtime = buf.st_atime; //文件的最后访问时间
        time_t stMtime = buf.st_mtime; //文件的最后修改时间
        printTime(stAtime, stMtime);   //打印时间

        //更新文件访问时间
        struct tm *tmAtime;            //文件的最后访问时间结构体形式
        tmAtime = localtime(&stAtime); //获取当前时间,结构体形式
        tmAtime->tm_hour += 1;
        tmAtime->tm_min += 5;
        stAtime = mktime(tmAtime); //将结构体时间转化为time_t 时间

        //更新文件最后修改时间
        struct tm *tmMtime;            //文件的最后访问时间结构体形式
        tmMtime = localtime(&stMtime); //获取当前时间,结构体形式
        tmMtime->tm_hour += 2;
        tmMtime->tm_min += 8;
        stMtime = mktime(tmMtime); //将结构体时间转化为time_t 时间

        cout << "==========更新文件时间==================" << endl;

        //更新文件时间
        struct utimbuf *timebuf = new utimbuf(); //创建一个结构体指针变量
        timebuf->actime = stAtime;
        timebuf->modtime = stMtime;
        rt = utime(pathname, timebuf); //更新文件时间
        if (rt == -1)
        {
            perror("utime error");
            cout << "更新文件时间失败:" << pathname << endl;
        }
        else
        {
            //获取更新后的文件时间
            rt = stat(pathname, &buf); //获取系统文件属性
            if (rt == -1)
            {
                perror("stat error");
                cout << "获取系统文件属性失败:" << pathname << endl;
            }
            else
            {
                stAtime = buf.st_atime;      //文件的最后访问时间
                stMtime = buf.st_mtime;      //文件的最后修改时间
                printTime(stAtime, stMtime); //打印时间
            }
        }
    }
    cout << endl;
}

/**
 * @brief 打印时间
 *
 * @param stAtime 文件最后访问时间
 * @param stMtime 文件最后修改时间
 */
void printTime(time_t stAtime, time_t stMtime)
{
    char *atime = ctime(&stAtime); //获取文件的最后访问时间字符串形式
    char *mtime = ctime(&stMtime); //获取文件的最后修改时间字符串形式
    cout << "文件的最后访问时间:" << atime << endl;
    cout << "文件的最后修改时间:" << mtime << endl;

    struct tm *tmAtime;            //文件的最后访问时间结构体形式
    tmAtime = localtime(&stAtime); //获取当前时间,结构体形式
    //字符串拼接
    int year = tmAtime->tm_year + 1900;
    int month = tmAtime->tm_mon + 1;
    int day = tmAtime->tm_mday;
    int hour = tmAtime->tm_hour;
    int minute = tmAtime->tm_min;
    int second = tmAtime->tm_sec;
    int week = tmAtime->tm_wday;
    std::string dateTime = to_string(year) + "年" + to_string(month) + "月" + to_string(day) + "日 " + to_string(hour) + ":" + to_string(minute) + ":" + to_string(second) + " 星期" + to_string(week);
    cout << "tmAtime=" << dateTime << endl;

    std::ostringstream oss;
    oss << year << "年" << month << "月" << day << "日 " << hour << ":" << minute << ":" << second << " 星期" << week;
    dateTime = oss.str();
    cout << "tmAtime2=" << dateTime << endl;

    struct tm *tmMtime;            //文件的最后访问时间结构体形式
    tmMtime = localtime(&stMtime); //获取当前时间,结构体形式

    //字符串拼接
    year = tmMtime->tm_year + 1900;
    month = tmMtime->tm_mon + 1;
    day = tmMtime->tm_mday;
    hour = tmMtime->tm_hour;
    minute = tmMtime->tm_min;
    second = tmMtime->tm_sec;
    week = tmMtime->tm_wday;
    dateTime = to_string(year) + "年" + to_string(month) + "月" + to_string(day) + "日 " + to_string(hour) + ":" + to_string(minute) + ":" + to_string(second) + " 星期" + to_string(week);
    cout << "tmMtime=" << dateTime << endl;

    std::ostringstream oss2;
    oss2 << year << "年" << month << "月" << day << "日 " << hour << ":" << minute << ":" << second << " 星期" << week;
    dateTime = oss2.str();
    cout << "tmMtime2=" << dateTime << endl;
}

/**
 * @brief 获取文件大小
 *
 * @param pathname 文件名
 * @return long int
 */
long int getFileSize(const char *pathname)
{
    struct stat statbuff; //系统文件属性
    long int size = 0;
    int rt = stat(pathname, &statbuff); //获取系统文件属性
    if (rt == -1)
    {
        perror("stat error");
        size = 0;
    }
    else
    {
        off_t len = statbuff.st_size; //获取文件大小
        size = len;
    }
    return size;
}

/**
 * @brief 改变文件长度
 *
 */
void test4()
{
    cout << "test4():: ..." << endl;
    const char *pathname = "./file/f3.txt"; //文件名
    int fd = open(pathname, O_RDWR);        //打开文件
    if (fd == -1)
    {
        perror("open error");
        cout << "打开文件失败:" << pathname << endl;
    }
    else
    {
        //先读取原来文件内容,并输出到屏幕文件
        int size = getFileSize(pathname);
        cout << "改变之前文件大小:" << size << endl;
        char buffer[100]; //缓冲区
        int number;       //读取到的字节数
        while ((number = read(fd, buffer, 100)) > 0)
        {
            write(1, buffer, number); //向屏幕文件输出
        }
        //改变文件长度
        int rt = truncate(pathname, size * 3 / 4);
        if (rt == -1)
        {
            perror("truncate error");
            cout << "改变文件长度失败:" << pathname << endl;
        }
        else
        {
            cout << "改变文件长度成功:" << pathname << endl;
            size = getFileSize(pathname);
            cout << "改变之后文件大小:" << size << endl;
            lseek(fd, 0, SEEK_SET); //文件指针定位到文件开头
            //再次读出改变后的文件内容
            memset(buffer, 0, sizeof(buffer)); //清空缓冲区
            while ((number = read(fd, buffer, sizeof(buffer))) > 0)
            {
                write(1, buffer, number); //向屏幕文件输出
            }
        }
        close(fd); //关闭文件
    }

    cout << endl;
}

void test5()
{
    cout << "test5():: ..." << endl;
    const char *pathname = "./file/f4.txt"; //文件名
    int fd = open(pathname, O_RDWR);        //打开文件
    if (fd == -1)
    {
        perror("open error");
        cout << "打开文件失败:" << pathname << endl;
    }
    else
    {
        //先读取原来文件内容,并输出到屏幕文件
        int size = getFileSize(pathname);
        cout << "改变之前文件大小:" << size << endl;
        char buffer[100]; //缓冲区
        int number;       //读取到的字节数
        while ((number = read(fd, buffer, 100)) > 0)
        {
            write(1, buffer, number); //向屏幕文件输出
        }
        //改变文件长度
        int rt = ftruncate(fd, size * 2);
        if (rt == -1)
        {
            perror("truncate error");
            cout << "改变文件长度失败:" << pathname << endl;
        }
        else
        {
            cout << "改变文件长度成功:" << pathname << endl;
            size = getFileSize(pathname);
            cout << "改变之后文件大小:" << size << endl;
            lseek(fd, 0, SEEK_SET); //文件指针定位到文件开头
            //再次读出改变后的文件内容
            memset(buffer, 0, sizeof(buffer)); //清空缓冲区
            while ((number = read(fd, buffer, sizeof(buffer))) > 0)
            {
                write(1, buffer, number); //向屏幕文件输出
            }
        }
        close(fd); //关闭文件
    }

    cout << endl;
}

/**
 * @brief 输出重定向
 *
 */
void test6()
{
    cout << "test6():: ..." << endl;
    const char *pathname = "./file/f5.txt"; //文件名
    int fd = open(pathname, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        perror("open error");
        cout << "打开文件失败:" << pathname << endl;
    }
    else
    {
        int rt = dup2(fd, 1); //把文件描述符fd复制到文件描述符1(标准输出)
        if (rt == -1)
        {
            perror("dup2 error");
            cout << "复制文件描述符失败:" << pathname << endl;
        }
        else
        {
            //输出重定向
            std::string content = "今天是周六,在家好舒服...";
            const char *content_str = content.c_str(); //字符串转换为字符数组
            printf("%s\n", content_str);
        }
        close(fd); //关闭文件
    }

    cout << endl;
}

void test7()
{
    cout << "test7():: ..." << endl;
    cout << endl;
}

void test8()
{
    cout << "test8():: ..." << endl;
    cout << endl;
}

void test9()
{
    cout << "test9():: ..." << endl;
    cout << endl;
}

void test10()
{
    cout << "test10():: ..." << endl;
    cout << endl;
}