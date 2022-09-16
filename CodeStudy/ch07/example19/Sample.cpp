#include "./include/Sample.h"

/**
 * @brief 从FIFO管道文件中将数据读出
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    const char *pathname = "../example18/fifo/test.fifo"; //管道文件名
    char buf[1024];                                       //缓冲区
    int fd;                                               //文件描述符
    int number = -2;                                      //读取的数据个数
    fd = open(pathname, O_RDWR);                          //打开管道文件
    if (fd == -1)
    {
        printf("打开管道文件失败\n");
        exit(0); //结束进程
    }
    number = read(fd, buf, sizeof(buf)); //从管道文件中读取数据
    if (number == -1)
    {
        printf("从管道文件中读取数据错误:%s\n", pathname);
        exit(0); //结束进程
    }
    buf[number] = '\0';
    printf("%s\n", buf); //打印读取出的数据
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