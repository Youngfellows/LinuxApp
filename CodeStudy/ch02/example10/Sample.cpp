#include "./include/Sample.h"

/**
 * @brief 获取命令行参数
 * @brief 使用: ./obj/test_sample.out
 * @brief 使用: ./obj/test_sample.out -h
 * @brief 使用: ./obj/test_sample.out -l
 * @brief 使用: ./obj/test_sample.out -l /etc/passwd
 * @brief 使用: ./obj/test_sample.out -l ./file
 * 
 * @param argc 参数个数
 * @param argv 参数列表
 *
 *
 */
void test1(int argc, char *argv[])
{
    cout << "test1():: ..." << endl;
    if (argc == 1)
    {
        cout << "使用: " << argv[0] << " [-l] [目录名/文件名]" << endl;
        return;
    }

    const char *optstring = "hl:";
    int optchar;              //返回选项参数中的选项字符
    opterr = 0;               //遇到未知的选项参数,或选项参数缺失时,返回？代表出错
    char *pathname = nullptr; //目录或者文件名称
    while ((optchar = getopt(argc, argv, optstring)) != -1)
    {
        printf("optchar=%c\n", optchar);
        switch (optchar)
        {
        case 'l':
            pathname = optarg;
            cout << pathname << endl;
            printf("%s\n", optarg);
            break;
        case 'h': //使用帮助
            cout << "使用: " << argv[0] << " [-l] [目录名/文件名]" << endl;
            // break;
            return;
        case '?':
            // optop存储的是未知的参数或缺失参数的选项字符
            if (optopt == 'l')
            {
                fprintf(stderr, "选项字符 \'-%c\' 需要一个参数\n", optopt);
            }
            else if (isprint(optopt))
            {
                fprintf(stderr, "未知的选项字符 \'-%c\'\n", optopt);
            }
            else
            {
                fprintf(stderr, "未知的选项字符 \'%x\'\n", optopt);
            }
            break;
        default:
            break;
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