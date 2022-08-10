#include "./include/Sample.h"

void test1()
{
    cout << "test1():: ..." << endl;
    //以只读方式打开文件
    const char *pathName = "./file/f1.text";
    int fd = open(pathName, O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        cout << "打开文件" << pathName << "失败 ..." << endl;
    }
    else
    {
        cout << "打开文件" << pathName << "成功 ..." << endl;
    }
    close(fd);
    cout << endl;
}

void test2()
{
    cout << "test2():: ..." << endl;
    //读写方式打开文件,不存在就创建,所有者可读写,所属组成员及其他用户只能读
    const char *fileName = "./file/f2.text";
    int fd = open(fileName, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1)
    {
        perror("open");
        cout << "打开文件" << fileName << "失败 ..." << endl;
    }
    else
    {
        cout << "打开文件" << fileName << "成功 ..." << endl;
    }
    close(fd);
    cout << endl;
}

void test3()
{
    cout << "test3():: ..." << endl;
    //读写方式打开文件,不存在就创建,所有者可读写,所属组成员及其他用户只能读,文件存在,返回错误
    const char *fileName = "./file/f3.text";
    int fd = open(fileName, O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1)
    {
        perror("open");
        cout << "打开文件" << fileName << "失败 ..." << endl;
    }
    else
    {
        cout << "打开文件" << fileName << "成功 ..." << endl;
    }
    close(fd);
    cout << endl;
}

void test4()
{
    cout << "test4():: ..." << endl;
    const char *f1 = "./file/f4.text";
    const char *f2 = "./file/f5.text";
    const char *f3 = "./file/f6.text";
    int fd1;
    int fd2;
    int fd3;
    fd1 = open(f1, O_RDWR);
    fd2 = open(f2, O_RDWR);
    fd3 = open(f3, O_RDWR);
    cout << "fd1=" << fd1 << ",fd2=" << fd2 << ",fd3=" << fd3 << endl;
    close(fd1);
    close(fd2);
    close(fd3);
    cout << endl;
}
void test5()
{
    cout << "test5():: ..." << endl;
    const char *f1 = "./file/f4.text";
    const char *f2 = "./file/f5.text";
    const char *f3 = "./file/f6.text";
    int fd1;
    int fd2;
    int fd3;
    fd1 = open(f1, O_RDWR);
    fd2 = open(f2, O_RDWR);
    close(fd1);
    cout << "fd1=" << fd1 << ",fd2=" << fd2 << endl;

    fd3 = open(f3, O_RDWR);
    cout << "fd3=" << fd3 << endl;

    close(fd2);
    close(fd3);
    cout << endl;
}
void test6()
{
    cout << "test6():: ..." << endl;
    //创建文件
    const char *file = "./file/f7.text";
    int fd = creat(file, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1)
    {
        perror("creat");
        cout << "创建文件" << file << "失败 ..." << endl;
    }
    else
    {
        cout << "创建文件" << file << "成功 ..." << endl;
    }
    close(fd);
    cout << endl;
}
void test7()
{
    cout << "test7():: ..." << endl;
    //读写文件
    const char *fileName = "./file/f8.txt";
    int fd;           //文件描述符
    int number;       //读取的字符数
    char buffer[100]; //缓冲区

    fd = open(fileName, O_RDONLY); //打开文件
    if (fd == -1)
    {
        perror("open");
        cout << "打开文件" << fileName << "失败 ..." << endl;
    }
    else
    {
        //读取文件
        while ((number = read(fd, buffer, 100)) > 0)
        {
            //写入屏幕文件
            if (write(1, buffer, number) < number)
            {
                cout << "写入屏幕文件少了 ..." << endl;
            }
        }
    }
    close(fd); //关闭文件
    cout << endl;
}
void test8()
{
    cout << "test8():: ..." << endl;
    //拷贝文件
    const char *sourceFile = "./file/f9.txt";
    const char *destFile = "./file/f10.txt";
    char buffer[100]; //缓冲区
    int number;       //读取的字节数
    int fd1;
    int fd2;

    fd1 = open(sourceFile, O_RDONLY); //打开文件
    if (fd1 == -1)
    {
        perror("open source file");
        cout << "打开文件" << sourceFile << ",失败 ..." << endl;
    }
    else
    {
        // fd2 = open(destFile, O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH); //打开并创建文件,存在则报错
        fd2 = open(destFile, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH); //打开并创建文件,,存在则覆盖
        if (fd2 == -1)
        {
            perror("open dest file");
            cout << "打开/创建文件" << destFile << ",失败 ..." << endl;
        }
        else
        {
            //读取文件
            while ((number = read(fd1, buffer, 100)) > 0)
            {
                write(fd2, buffer, number); //写文件,拷贝文件
            }
        }
        close(fd2); //关闭文件
    }
    close(fd1); //关闭文件
    cout << endl;
}
void test9()
{
    cout << "test9():: ..." << endl;
    //两次打开同一个文件
    //拷贝文件
    const char *sourceFile = "./file/f11.txt";
    const char *destFile = "./file/f12.txt";
    char buffer[100]; //缓冲区
    int number;       //读取的字节数
    int fd1;
    int fd2;
    int fd3;

    fd1 = open(sourceFile, O_RDONLY); //打开文件
    if (fd1 == -1)
    {
        perror("open source file");
        cout << "打开文件" << sourceFile << ",失败 ..." << endl;
    }
    else
    {
        // fd2 = open(destFile, O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH); //打开并创建文件,存在则报错
        fd2 = open(destFile, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH); //打开并创建文件,,存在则覆盖
        if (fd2 == -1)
        {
            perror("open dest file");
            cout << "打开/创建文件" << destFile << ",失败 ..." << endl;
        }
        else
        {
            //读取文件
            while ((number = read(fd1, buffer, 100)) > 0)
            {
                write(fd2, buffer, number); //写文件,拷贝文件
            }

            //另外一个文件描述符读写入的文件内容
            fd3 = open(destFile, O_RDWR); //第2次打开目标文件
            if (fd3 == -1)
            {
                perror("open dest file");
                cout << "打开文件" << destFile << ",失败 ..." << endl;
            }
            else
            {
                //读取刚刚写入文件的文件
                while ((number = read(fd3, buffer, 100)) > 0)
                {
                    //写入屏幕文件
                    if ((write(1, buffer, number) < number))
                    {
                        cout << "写入屏幕文件的字节少了 ..." << endl;
                    }
                }
            }
        }
        close(fd2); //关闭文件
    }
    close(fd1); //关闭文件
    cout << endl;

    cout << endl;
}

void test10()
{
    cout << "test10():: ..." << endl;
    //复制文件
    const char *from = "./file/f14.txt";
    const char *to = "./file/f15.txt";
    char buffer[100]; //缓冲区
    int number;       //读取的字节数
    int fromfd;       //文件描述符
    int tofd;         //文件描述符

    fromfd = open(from, O_RDONLY); //打开文件
    if (fromfd == -1)
    {
        perror("open source file");
        cout << "打开文件" << from << ",失败 ..." << endl;
    }
    else
    {
        // fd2 = open(destFile, O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH); //打开并创建文件,存在则报错
        tofd = open(to, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH); //打开并创建文件,,存在则覆盖
        if (tofd == -1)
        {
            perror("open dest file");
            cout << "打开/创建文件" << to << ",失败 ..." << endl;
        }
        else
        {
            //读取文件
            while ((number = read(fromfd, buffer, 100)) > 0)
            {
                write(tofd, buffer, number); //写文件,拷贝文件
            }
        }
        close(tofd); //关闭文件
    }
    close(fromfd); //关闭文件
    cout << endl;
}

void test11()
{
    cout << "test11():: ..." << endl;
    cout << endl;
}

void test12()
{
    cout << "test12():: ..." << endl;
    cout << endl;
}

void test13()
{
    cout << "test13():: ..." << endl;
    cout << endl;
}

void test14()
{
    cout << "test14():: ..." << endl;
    cout << endl;
}

void test15()
{
    cout << "test15():: ..." << endl;
    cout << endl;
}

void test16()
{
    cout << "test16():: ..." << endl;
    cout << endl;
}

void test17()
{
    cout << "test17():: ..." << endl;
    cout << endl;
}