#include "./include/Sample.h"

void test1()
{
    cout << "test1():: ..." << endl;
    //向文件中写入内容,然后读出并显示到屏幕上
    std::string content = "通知,国庆放假七天,大家准备好加班吧,大哭 ....";
    const char *contentBuffer = content.c_str(); //字符串转化为字符数组
    int len = content.size();                    //字符串大小
    cout << "len:" << len << "," << contentBuffer << endl;

    const char *pathName = "./file/f1.txt";
    int fd;                       //文件描述符
    char *buffer = new char[len]; //动态申请内存
    int number;                   //读取的字符数

    fd = open(pathName, O_RDWR | O_CREAT | O_TRUNC, 0644); //打开文件,不存在,创建文件,如果已经存在,置空
    if (fd == -1)
    {
        perror("open error");
        cout << "打开文件" << pathName << ",错误 ..." << endl;
    }
    else
    {
        number = write(fd, contentBuffer, len); //向文件中写入内容
        cout << "写入文件内容" << number << "个字节" << endl;
        if (number < len)
        {
            cout << "可能是内存不足,写入的内容少了 ..." << endl;
        }
        lseek(fd, 0, SEEK_SET);         //文件指针定位到文件开头
        number = read(fd, buffer, len); //读取文件内容,放入缓冲区
        if (number != len)
        {
            cout << "读取到的内容少了 ..." << endl;
        }
        write(1, buffer, number); //向屏幕文件写入内容
    }
    close(fd);       //关闭流
    delete[] buffer; //释放内存,释放数组
    cout << endl;
}

void test2()
{
    cout << "test2():: ..." << endl;
    //向文件中写入内容,然后读出并显示到屏幕上
    std::string content = "中秋节,我要出去旅游啦,开心 ....";
    const char *contentBuffer = content.c_str(); //字符串转化为字符数组
    int len = content.size();                    //字符串大小
    cout << "len:" << len << "," << contentBuffer << endl;

    const char *pathName = "./file/f2.txt";
    int fd;                       //文件描述符
    char *buffer = new char[len]; //动态申请内存
    int number;                   //读取的字符数

    fd = open(pathName, O_RDWR | O_CREAT | O_TRUNC, 0644); //打开文件,不存在,创建文件,如果已经存在,置空
    if (fd == -1)
    {
        perror("open error");
        cout << "打开文件" << pathName << ",错误 ..." << endl;
    }
    else
    {
        number = write(fd, contentBuffer, len); //向文件中写入内容
        cout << "写入文件内容" << number << "个字节" << endl;
        if (number < len)
        {
            cout << "可能是内存不足,写入的内容少了 ..." << endl;
        }
        lseek(fd, 4, SEEK_SET);        //文件指针定位到文件开头4的位置
        number = read(fd, buffer, 20); //读取6个字节文件内容,放入缓冲区
        if (number != 20)
        {
            cout << "读取到的内容少了 ..." << endl;
        }
        write(1, buffer, number); //向屏幕文件写入内容
    }
    close(fd);       //关闭流
    delete[] buffer; //释放内存,释放数组
    cout << endl;
}

void test3()
{
    cout << "test3():: ..." << endl;
    //向文件中写入内容,然后截取文件内容,再读出并显示到屏幕上
    std::string content = "大家辛苦啦,周末愉快哦 ....";
    const char *contentBuffer = content.c_str(); //字符串转化为字符数组
    int len = content.size();                    //字符串大小
    cout << "len:" << len << "," << contentBuffer << endl;

    const char *pathName = "./file/f3.txt";
    int fd;                       //文件描述符
    char *buffer = new char[len]; //动态申请内存
    int number;                   //读取的字符数

    fd = open(pathName, O_RDWR | O_CREAT | O_TRUNC, 0644); //打开文件,不存在,创建文件,如果已经存在,置空
    if (fd == -1)
    {
        perror("open error");
        cout << "打开文件" << pathName << ",错误 ..." << endl;
    }
    else
    {
        number = write(fd, contentBuffer, len); //向文件中写入内容
        cout << "写入文件内容" << number << "个字节" << endl;
        if (number < len)
        {
            cout << "可能是内存不足,写入的内容少了 ..." << endl;
        }
        lseek(fd, 0, SEEK_SET);        //文件指针定位到文件开头的位置
        ftruncate(fd, 20);             //截取文件内容,20个字节
        number = read(fd, buffer, 20); //读取6个字节文件内容,放入缓冲区
        if (number != 20)
        {
            cout << "读取到的内容少了 ..." << endl;
        }
        write(1, buffer, number); //向屏幕文件写入内容
    }
    close(fd);       //关闭流
    delete[] buffer; //释放内存,释放数组
    cout << endl;
}

void test4()
{
    cout << "test4():: ..." << endl;
    //读取文件内容
    const char *pathName = "./file/f4.txt";
    int fd;           //文件描述符
    int number;       //读取的字节数
    char buffer[100]; //缓冲区

    fd = open(pathName, O_RDONLY); //打开文件
    if (fd == -1)
    {
        perror("open error");
        cout << "打开文件" << pathName << ",失败 ..." << endl;
    }
    else
    {
        //循环读取文件
        while ((number = read(fd, buffer, 100)) > 0)
        {
            write(1, buffer, number); //向屏幕文件写入读取到的内容
        }
    }
    close(fd); //关闭文件
    cout << endl;
}

void test5()
{
    cout << "test5():: ..." << endl;
    //读取f4.txt文件内容,并拷贝到f5.txt文件
    const char *from = "./file/f4.txt";
    const char *to = "./file/f5.txt";
    int fromfd;       //文件描述符
    int tofd;         //文件描述符
    int number;       //读取的字节数
    char buffer[100]; //缓冲区

    fromfd = open(from, O_RDONLY); //打开文件
    if (fromfd == -1)
    {
        perror("open error");
        cout << "打开文件" << from << ",失败 ..." << endl;
    }
    else
    {
        tofd = open(to, O_WRONLY | O_CREAT | O_TRUNC, 0644); //创建并打开文件
        if (tofd == -1)
        {
            perror("open error");
            cout << "打开文件" << to << ",失败 ..." << endl;
        }
        else
        {
            //循环读取文件
            while ((number = read(fromfd, buffer, 100)) > 0)
            {
                write(tofd, buffer, number); //向文件中写入读取到的内容
                write(1, buffer, number);    //向屏幕文件写入读取到的内容
            }
        }
        close(tofd); //关闭文件
    }
    close(fromfd); //关闭文件
    cout << endl;
}