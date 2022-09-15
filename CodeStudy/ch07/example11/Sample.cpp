#include "./include/Sample.h"

/**
 * @brief 1. 设置新的信号屏蔽字
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    sigset_t set;                //设置的信号屏蔽字
    sigset_t oldSet;             //旧的信号屏蔽字
    int member;                  //信号是否在屏蔽字中
    if (sigemptyset(&set) == -1) //清空信号集set
    {
        printf("清空信号集错误\n");
        exit(1);
    }
    if (sigaddset(&set, SIGINT) == -1) //将SIGINT加入set
    {
        printf("将SIGINT加入set错误\n");
        exit(2);
    }
    //设置信号屏蔽字为set,并使用oldSet保存原屏蔽字
    if (sigprocmask(SIG_SETMASK, &set, &oldSet) == -1)
    {
        printf("设置信号屏蔽字错误\n");
        exit(3);
    }
    //判断SIGINT是否在原屏蔽字中
    member = sigismember(&oldSet, SIGINT);
    if (member == 1)
    {
        printf("SIGINT信号在原始信号屏蔽字oldSet中\n");
    }
    else if (member == 0)
    {
        printf("SIGINT信号不在在原始信号屏蔽字oldSet中\n");
    }
    else
    {
        printf("调用sigismember函数错误\n");
    }

    member = sigismember(&set, SIGINT);
    if (member == 1)
    {
        printf("SIGINT信号在信号屏蔽字set中\n");
    }
    else if (member == 0)
    {
        printf("SIGINT信号不在信号屏蔽字set中\n");
    }
    else
    {
        printf("调用sigismember函数错误\n");
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