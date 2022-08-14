#include "./include/Sample.h"

/**
 * @brief 实现cd 命令切换当前目录
 *
 */
void test1(int argc, char *argv[])
{
    cout << "test1():: ..." << endl;
    char workdir[100];    //当前工作目录
    getcwd(workdir, 100); //先获取当前目录
    printf("当前工作目录:%s\n", workdir);

    //获取命令行参数
    if (argc == 1)
    {
        char *homepath = getenv("HOME"); //获取环境变量HOME对于的home家目录
        printf("home:%s\n", homepath);
        printf("before:\n");
        system("pwd");
        chdir(homepath); //切换到home目录
        printf("after:\n");
        system("pwd");

        //再切回当前工作目录
        chdir(workdir);
        printf("finial:\n");
        system("pwd");
    }
    else
    {
        printf("before:\n");
        system("pwd");
        //切换到指定目录
        if (chdir(argv[1]) == -1)
        {
            perror("chdir");
        }
        printf("after:\n");
        system("pwd");

        //再切回当前工作目录
        chdir(workdir);
        printf("finial:\n");
        system("pwd");
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