#include "./include/Sample.h"

/**
 * @brief 1. 获得进程被屏蔽的信号
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    sigset_t oldSet;                                //信号集
    int member;                                     //信号是否包含在信号集中
    if (sigprocmask(SIG_BLOCK, NULL, &oldSet) == 0) //获取当前信号屏蔽子
    {
        //判断当前信号屏蔽字是否包含SIGINT
        member = sigismember(&oldSet, SIGINT);
        if (member == 1)
        {
            printf("当前信号屏蔽字包含信号:SIGINT\n");
        }
        else if (member == 0)
        {
            printf("当前信号屏蔽字不包含信号:SIGINT\n");
        }
        else
        {
            printf("调用sigismember错误\n");
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