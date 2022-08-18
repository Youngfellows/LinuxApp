#include "./include/Sample.h"

/**
 * @brief 等待指定pid的子进程结束
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    int status;         //子进程结束时返回的退出状态
    pid_t pids[CHILDS]; //子进程数组
    pid_t waitPid = -1; //结束子进程的pid
    for (int i = 0; i < CHILDS; i++)
    {
        pids[i] = fork(); //创建5个子进程
        if (pids[i] == -1)
        {
            perror("fork failed");
            exit(-1);
        }
        else if (pids[i] == 0)
        {
            printf("子进程pid=%d,ppid=%d\n", getpid(), getppid());
            sleep(i); //休眠一下
            exit(i);  //正常终止子进程
        }
    }
    //等待某个子进程结束
    waitPid = waitpid(pids[2], &status, 0); //等待pids[4]子进程结束
    printf("%d,进程执行了,子进程%d结束的,状态是%d\n", getpid(), waitPid, status);

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