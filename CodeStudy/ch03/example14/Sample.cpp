#include "./include/Sample.h"

/**
 * @brief 获取进程的退出状态
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    int status;   //子进程结束时的终止状态
    pid_t pid;    //进程pid
    pid = fork(); //创建子进程
    if (pid == -1)
    {
        perror("fork error");
        cout << "创建子进程失败..." << endl;
        exit(0);
    }
    else if (pid == 0)
    {
        printf("子进程pid=%d\n", getpid());
        exit(0); //子进程正常退出
    }
    else
    {
        printf("父进程pid=%d\n", getpid());
        //等待子进程退出,并返回子进程的终止状态
        pid_t id = wait(&status);
        printf("父进程pid=%d,%d子进程的终止状态:%d\n", getpid(), id, status);

        if (WIFEXITED(status)) //正常终止子进程
        {
            printf("正常终止子进程,子进程的退出状态为%d\n", WEXITSTATUS(status));
        }
        else
        {
            printf("异常终止子进程,子进程的退出状态为%d\n", WEXITSTATUS(status));
        }

        if (WIFSIGNALED(status)) //是否被某个信号终止子进程
        {
            printf("被%d信号终止子进程\n", WTERMSIG(status));
        }
        else
        {
            printf("不是被信号终止子进程\n");
        }
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