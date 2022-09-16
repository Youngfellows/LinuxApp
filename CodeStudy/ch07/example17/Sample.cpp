#include "./include/Sample.h"

/**
 * @brief 管道写入端关闭,管道读出端返回0字节
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    pid_t pid;  //进程ID
    int fds[2]; //管道读出端,写入端
    const char *data = "今天是周五,马上下班了,祝大家周末愉快 ...\n";
    int size = strlen(data); //求字符串的大小
    printf("data size:%d\n", size);
    char buf[size] = {0}; //缓冲区
    //设置当前进程对SIGCHLD信号的捕捉函数
    if (signal(SIGCHLD, signalHandler) == SIG_ERR)
    {
        printf("设置当前进程对SIGCHLD信号的捕捉函数错误\n");
        exit(0); //结束进程
    }

    if (pipe(fds) == 0) //创建管道
    {
        pid = fork(); //创建子进程
        if (pid == 0) //子进程
        {
            pid_t self = getpid(); //获取进程ID
            printf("子进程pid:%d\n", self);
            close(fds[0]);                     //关闭子进程管道读出端
            signal(SIGCHLD, SIG_DFL);          //设置子进程对SIGCHLD信号默认处理方式
            signal(SIGPIPE, signalHandler);    //设置子进程对SIGPIPE信号捕捉处理方式
            write(fds[1], data, strlen(data)); //子进程写data到管道
            printf("子进程等待3秒,等待父进程读出数据\n");
            sleep(3);      //等待3秒
            close(fds[1]); //子进程关闭管道写入端
        }
        else if (pid > 0) //父进程
        {
            pid_t self = getpid(); //获取进程ID
            printf("父进程pid:%d\n", self);
            close(fds[1]); //关闭父进程管道写入端
            // wait(nullptr); //等待子进程执行完成
            printf("父进程等待2秒,等待子进程写入数据\n");
            sleep(2);
            int number = -2;                         //读出的数据大小
            number = read(fds[0], buf, sizeof(buf)); //父进程读出端读出管道数据
            if (number == -1)
            {
                perror("父进程读取数据错误");
            }
            else
            {
                printf("父进程读到长度%d的数据,内容是:%s\n", number, buf);
            }

            printf("父进程再等待3秒,子进程已经退出了\n");
            sleep(3);
            number = read(fds[0], buf, sizeof(buf)); //父进程读出端读出管道数据
            if (number == -1)
            {
                perror("父进程读取数据错误");
            }
            else
            {
                printf("父进程读到长度%d的数据,内容是:%s\n", number, buf);
            }
        }
    }
    else
    {
        printf("创建管道失败\n");
        exit(0);
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
    case SIGPIPE:
        printf("捕捉到SIGPIPE信号,管道读出端不存在 ...\n");
        break;
    case SIGCHLD:
        printf("捕捉到SIGCHLD信号,子进程存在 ...\n");
        break;
    default:
        break;
    }
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