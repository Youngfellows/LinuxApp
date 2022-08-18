#include "./include/Sample.h"

/**
 * @brief 在子进程地址空间运行新的程序
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    const char *pathname = "./file/f1.txt"; //文件路径
    int fd;                                 //文件描述符
    pid_t pid;                              //进程pid
    printf("进程创建前\n");
    pid = fork(); //创建进程
    if (pid < 0)
    {
        perror("fork error");
    }
    else if (pid == 0)
    {
        printf("子进程:%d\n", getpid());
        fd = open(pathname, O_RDWR | O_CREAT | O_TRUNC, 0644); //创建并打开文件,如果存在则置空
        if (fd == -1)
        {
            perror("open error");
            exit(1);
        }
        dup2(fd, 1); //重定向标准输出到文件pathname
                     //在子进程地址空间运行新的程序
        execl("/bin/ls", "ls", "-l", NULL);
        perror("execl failed");
    }
    else
    {
        printf("父进程:%d\n", getpid());
    }
    printf("pid=%d,进程执行...\n", getpid());
    exit(0);
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