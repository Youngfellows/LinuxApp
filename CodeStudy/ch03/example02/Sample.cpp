#include "./include/Sample.h"

/**
 * @brief 获取当前进程的pid
 * @brief 获取当前进程的父进程pid
 * @brief 获取实际用户ID
 * @brief 获取有效用户ID
 * @brief 获取实际用户组ID
 * @brief 获取有效用户组ID
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    pid_t pid = getpid();
    pid_t ppid = getppid();
    uid_t uid = getuid();
    uid_t euid = geteuid();
    gid_t gid = getgid();
    gid_t egid = getegid();

    printf("pid=%d\n", pid);
    printf("ppid=%d\n", ppid);
    printf("uid=%d\n", uid);
    printf("euid=%d\n", euid);
    printf("gid=%d\n", gid);
    printf("egid=%d\n", egid);

    cout << endl;
}

void test2()
{
    cout << "test2():: ..." << endl;
    pid_t pid;    //进程pid
    pid = fork(); //创建一个子进程
    if (pid < 0)
    {
        perror("fork error");
        exit(1);
    }
    else if (pid == 0)
    {
        //子进程
        pid_t id = getpid();
        printf("子进程,pid=%d\n", id);
    }
    else
    {
        //父亲进程
        printf("父进程,pid=%d\n", getpid());
    }
    printf("%d 进程执行打印...\n", getpid());

    cout << endl;
}

/**
 * @brief 体会父子进程的先后执行顺序
 *
 */
void test3()
{
    cout << "test3():: ..." << endl;
    pid_t id; //进程PID
    int i;
    id = fork(); //创建一个子进程
    if (id < 0)
    {
        perror("fork error");
        exit(1);
    }
    else if (id == 0)
    {
        //子进程
        for (i = 0; i < 10; i++)
        {
            printf("子进程,pid=%d\n", getpid());
            sleep(1);
        }
    }
    else
    {
        //父进程
        for (i = 0; i < 10; i++)
        {
            printf("父进程,pid=%d\n", getpid());
            sleep(1);
        }
    }
    printf("%d 进程执行了\n", getpid());
    cout << endl;
}

void test4()
{
    cout << "test4():: ..." << endl;
    cout << endl;
}

void test5()
{
    cout << "test5():: ..." << endl;
    cout << endl;
}

void test6()
{
    cout << "test6():: ..." << endl;
    cout << endl;
}

void test7()
{
    cout << "test7():: ..." << endl;
    cout << endl;
}

void test8()
{
    cout << "test8():: ..." << endl;
    cout << endl;
}

void test9()
{
    cout << "test9():: ..." << endl;
    cout << endl;
}

void test10()
{
    cout << "test10():: ..." << endl;
    cout << endl;
}

void test11()
{
    cout << "test11():: ..." << endl;
    cout << endl;
}

void test12()
{
    cout << "test12():: ..." << endl;
    cout << endl;
}

void test13()
{
    cout << "test13():: ..." << endl;
    cout << endl;
}

void test14()
{
    cout << "test14():: ..." << endl;
    cout << endl;
}

void test15()
{
    cout << "test15():: ..." << endl;
    cout << endl;
}

void test16()
{
    cout << "test16():: ..." << endl;
    cout << endl;
}

void test17()
{
    cout << "test17():: ..." << endl;
    cout << endl;
}

void test18()
{
    cout << "test18():: ..." << endl;
    cout << endl;
}

void test19()
{
    cout << "test19():: ..." << endl;
    cout << endl;
}

void test20()
{
    cout << "test20():: ..." << endl;
    cout << endl;
}
