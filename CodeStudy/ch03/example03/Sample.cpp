#include "./include/Sample.h"

int global = 0;                                //定义一个全局变量
char buf[] = "今天下雨哦,出门记得带雨伞...\n"; //写入的内容

/**
 * @brief 子进程赋值了父进程的地址空间
 * @brief 测试: ./obj/test_sample.out
 * @brief 测试: ./obj/test_sample.out > out
 */
void test1()
{
    cout << "test1():: ..." << endl;
    int var = 0;                                    //局部变量
    pid_t pid;                                      //进程PID
    if (write(STDOUT_FILENO, buf, strlen(buf)) < 0) //向标准输出流中写入数据
    {
        perror("write error");
    }
    printf("线程创建前\n");
    pid = fork(); //创建线程
    if (pid < 0)
    {
        perror("fork error");
        exit(1);
    }
    else if (pid == 0)
    {
        printf("子进程,pid=%d\n", getpid());
        global++;
        var++;
    }
    else
    {
        printf("父进程,pid=%d\n", getpid());
        sleep(1);
    }
    printf("pid=%d,global=%d,var=%d\n", getpid(), global, var);
    exit(0); //退出进程
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