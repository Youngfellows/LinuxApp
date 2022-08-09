#include "./include/Sample.h"

/**
 * @brief 获取命令行参数,选项参数以-开头
 *
 * @brief 测试: ./obj/test_sample.out
 * @brief 测试: ./obj/test_sample.out aa bb cc
 * @brief 测试: ./obj/test_sample.out  -a
 * @brief 测试: ./obj/test_sample.out  -a -b
 * @brief 测试: ./obj/test_sample.out  -ba
 * @brief 测试: ./obj/test_sample.out  -ab
 * @brief 测试: ./obj/test_sample.out  -a -b -c
 * @brief 测试: ./obj/test_sample.out  -a -b -c foo
 * @brief 测试: ./obj/test_sample.out  -abc foo
 * @brief 测试: ./obj/test_sample.out arg1 -a arg2 -b arg3 -c foo arg4
 * @brief 测试:
 * @brief 测试:
 *
 * @param arg 参数个数
 * @param args 参数列表
 */
void test1(int arg, char *args[])
{
    cout << "test1():: ..." << endl;
    printArgv(arg, args);
    int para_a = 0;         //参数a
    int para_b = 0;         //参数b
    char *para_c = nullptr; //参数c
    int optchar;            //获取命令行参数
    opterr = 0;             //返回？代表出错

    while ((optchar = getopt(arg, args, "abc:")) != -1)
    {
        cout << "test1():: optchar:" << optchar << endl;
        switch (optchar)
        {
        case 'a':
            para_a = 1;
            break;
        case 'b':
            para_b = 1;
            break;
        case 'c':
            para_c = optarg; //冒号:或者双冒号::后面跟随的参数
            break;
        case '?': //出错
            if (optopt == 'c')
            {
                fprintf(stderr, "选项 - %c 需要一个参数\n", optopt);
                cout << "选项 - " << optopt << " 需要一个参数" << endl;
            }
            else if (isprint(optopt)) //是可打印字符
            {
                fprintf(stderr, "未知选项 - %c\n", optopt);
                cout << "未知选项 - " << optopt << endl;
            }
            else
            {
                fprintf(stderr, "未知选项字符 '\\x%x'\n", optopt);
                cout << "未知选项字符" << optopt << endl;
            }
            break;
        default:
            abort();
        }
    }
    cout << "==================" << endl;
    printArgv(arg, args);
    cout << "para_a=" << para_a << ",para_b=" << para_b << ",para_c=" << para_c << endl;
    cout << endl;
    //遍历非选项参数
    for (int i = optind; i < arg; i++)
    {
        // cout << "非选项参数:" << args[i] << endl;
        cout << "非选项参数:" << *(args + i) << endl;
    }
    cout << endl;
}

/**
 * @brief 测试: ./obj/test_sample.out  -abc fff
 *
 */
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

/**
 * @brief 打印命令行参数
 *
 * @param argc 参数个数
 * @param argv 参数列表
 */
void printArgv(int argc, char **argv)
{
    for (int i = 0; i < argc; i++)
    {
        char *param = argv[i];
        cout << "argv[" << i << "]=" << param << endl;
    }
}