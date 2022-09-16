#include "./include/Sample.h"

/**
 * @brief 使用FIFO有名管道实现在进程间通信
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    const char *pathname = "./fifo/test.fifo"; //管道文件名称
    int fd;                                    //文件描述符
    int rtn;
    if (mkfifo(pathname, 0644) == -1)
    {
        if (errno == EEXIST)
        {
            printf("管道文件已经存在:%s\n", pathname);
        }
    }
    fd = open(pathname, O_RDWR); //打开管道文件
    if (fd == -1)
    {
        printf("打开FIFO管道文件失败:%s\n", pathname);
        exit(1); //结束进程
    }
    const char *data = "还有3个星期就国庆啦,我们要去哪里玩呢 ...";
    rtn = write(fd, data, strlen(data)); //向有名管道文件写入数据
    if (rtn == -1)
    {
        printf("向有名管道文件写入数据错误:%s\n", pathname);
        exit(1); //结束进程
    }
    pause(); //等待管道读出端读出数据
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