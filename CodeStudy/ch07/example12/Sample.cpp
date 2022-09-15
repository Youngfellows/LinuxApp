#include "./include/Sample.h"

/**
 * @brief 获取未决信号
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    int rtn;         //处理结果
    sigset_t set;    //信号集
    sigset_t oldSet; //原始信号屏蔽字集合
    if (signal(SIGINT, signalHandler) == SIG_ERR)
    {
        printf("注册信号SIGQUIT的信号处理函数错误\n");
        exit(1);
    }
    rtn = sigpending(&set); //获取未决信号,存入set
    if (rtn == 0)
    {
        rtn = sigismember(&set, SIGINT); //判断SIGINT是否在未决信号中
        if (rtn == 1)
        {
            printf("SIGINT信号在未决信号中\n");
        }
        else
        {
            printf("SIGINT信号不在未决信号中\n");
        }
    }
    else
    {
        printf("获取未决信号错误\n");
        exit(1);
    }
    sigemptyset(&set);       //清空信号集
    sigaddset(&set, SIGINT); //将SIGINT信号添加到set信号集中
    //设置信号屏蔽字为set,并使用oldSet保存原屏蔽字
    if (sigprocmask(SIG_SETMASK, &set, &oldSet) == -1)
    {
        printf("设置新的信号屏蔽字错误\n");
    }
    printf("休眠5秒或者按下Ctrl + C\n");
    sleep(5);               //等待用户5秒,以便于用户按下Ctrl + C
    sigemptyset(&set);      //清空信号集合
    rtn = sigpending(&set); //获取未决信号,存入set
    if (rtn == 0)
    {
        rtn = sigismember(&set, SIGINT); //判断SIGINT是否在未决信号中
        if (rtn == 1)
        {
            printf("SIGINT信号在未决信号中\n");
        }
        else
        {
            printf("SIGINT信号不在未决信号中\n");
        }
    }
    else
    {
        printf("获取未决信号错误\n");
        exit(1);
    }

    //将set中的信号从当前屏蔽字中移除
    if (sigprocmask(SIG_UNBLOCK, &set, nullptr) == -1)
    {
        printf("将set中的信号从当前屏蔽字中移除错误\n");
        exit(1);
    }
    sigprocmask(SIG_SETMASK, &oldSet, nullptr); //恢复原始信号屏蔽字
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
    case SIGINT:
        printf("捕捉到信号:SIGINT\n");
        break;
    default:
        printf("捕捉到信号:%d\n", sig);
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