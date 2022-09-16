#include "./include/Sample.h"

/**
 * @brief 获取系统中管道缓冲区的大小
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    printf("系统中管道缓冲区的大小:%d(字节)\n", PIPE_BUF);

    cout << endl;
}

/**
 * @brief 1. 实现父子进程通过管道传输数据
 *
 */
void test2()
{
    cout << "test2():: ..." << endl;
    pid_t pid;  //进程ID
    int fds[2]; // fds[0]管道读出端文件描述符,fds[1]管道写入端文件描述符
    const char *data = "今天天气真的很不错 ...\n";
    int size = strlen(data);
    printf("size:%d\n", size);
    char buf[size] = {0};
    printf("buf size:%ld\n", sizeof(buf));

    if (pipe(fds) == 0) //创建管道
    {
        pid = fork(); //创建子进程
        if (pid == 0) //子进程
        {
            close(fds[0]);                     //关闭子进程的读出端
            write(fds[1], data, strlen(data)); //子进程向管道的写入端写入数据
            exit(0);                           //结束子进程
        }
        else if (pid > 0) //父进程
        {
            wait(NULL);                     //等待子进程结束
            close(fds[1]);                  //关闭父进程管道的写入端
            read(fds[0], buf, sizeof(buf)); //从管道的读入端读入数据
            printf("%s\n", buf);
        }
    }
    else
    {
        printf("创建管道失败...\n");
        exit(1);
    }

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