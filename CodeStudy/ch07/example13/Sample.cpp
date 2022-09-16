#include "./include/Sample.h"

/**
 * @brief 全局变量SUM
 *
 */
int sum = 0;

/**
 * @brief 1. 接受SIGALRM信号,并把sum的值写入文件
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    int rtn;
    if (signal(SIGALRM, signalHandler) != SIG_ERR)
    {
        rtn = alarm(6); //设置3秒定时器
        for (int i = 0; i < 10; i++)
        {
            sum += i;
            sleep(1);
        }
    }

    cout << endl;
}

/**
 * @brief 信号处理函数
 *
 * @param sig 信号
 */
void signalHandler(int sig)
{
    printf("signalHandler begin ...\n");
    switch (sig)
    {
    case SIGALRM:
        printf("捕捉到信号SIGALRM,sum:%d\n", sum);
        writeToFile();
        break;
    default:
        printf("捕捉到其他信号:%d\n", sig);
        break;
    }
}

/**
 * @brief 写入到文件
 *
 */
void writeToFile()
{
    const char *pathname = "./file/sumfile.txt";
    int fd;                                                //文件描述符
    int num;                                               //写入文件字节数
    fd = open(pathname, O_CREAT | O_RDWR | O_TRUNC, 0644); //创建并打开文件
    if (fd == -1)
    {
        perror("open file failed");
        exit(1); //结束进程
    }
    char *buf = new char[sizeof(int)];
    sprintf(buf, "%d", sum);
    printf("%s\n", buf);

    char num2[10];
    //_itoa(sum, num2, 10);
    // printf("%s\n", num2);

    num = write(fd, buf, strlen(buf)); //向文件写入数据
    printf("写入数据成功\n");
    close(fd); //关闭文件
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