#include "./include/Sample.h"

/**
 * @brief 两个子进程通过管道进行通信
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    pid_t pid1; //进程ID
    pid_t pid2; //进程ID
    int fds[2]; //管道读入端和写出端
    if (pipe(fds) == 0)
    {
        pid1 = fork(); //创建子进程pid1
        if (pid1 == 0) //子进程pid1
        {
            close(fds[0]);         //关闭读出端
            pid_t self = getpid(); //获取进程ID
            printf("子进程pid1=%d\n", self);
            write(fds[1], &self, sizeof(int)); //向管道写入端写入数据
            exit(1);                           //结束子进程1
        }
        pid2 = fork(); //创建子进程pid2
        if (pid2 == 0)
        {
            printf("子进程pid2=%d\n", getpid());
            close(fds[1]); //关闭管道写入端
            pid_t sibling;
            read(fds[0], &sibling, sizeof(int)); //从管道读入端读出数据
            printf("sibling pid = %d\n", sibling);
            exit(2); //结束子进程2
        }
    }
    else
    {
        printf("创建管道失败\n");
        exit(0);
    }

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