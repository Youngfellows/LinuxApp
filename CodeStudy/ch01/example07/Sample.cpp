#include "./include/Sample.h"

void test1(int argc, char *argv[])
{
    cout << "test1():: ..." << endl;
    //解析命令行参数
    if (argc == 1)
    {
        cout << "命令行没有参数 ..." << endl;
        return;
    }
    if (argc == 2)
    {
        char *p = argv[1];
        if (strcmp(p, "-a") == 0)
        {
            cout << "将要处理-a" << endl;
        }
        else if (strcmp(p, "-l") == 0)
        {
            cout << "将要处理-l" << endl;
        }
        else
        {
            cout << "不支持的参数:" << p << endl;
        }
    }
    else
    {
        cout << "命令行参数多了 ..." << endl;
    }

    cout << endl;
}

/**
 * @brief 将字符串转化为整数
 * @brief 函数原型: long int strtol(const char *str, char **endptr, int base);
 *
 */
void test2()
{
    cout << "test2():: ..." << endl;
    char str[30] = "20220809 This is test"; //字符串
    char *ptr = nullptr;                    //下一个字符
    int date;                               //转化后的数字
    date = strtol(str, &ptr, 10);           //将字符串转化为整数
    cout << "数字是:date=" << date << endl;
    cout << "字符串部分是:ptr=" << ptr << endl;
    cout << endl;
}

/**
 * @brief 解析命令行
 *
 */
void test3()
{
    cout << "test3():: ..." << endl;
    char *test_str = "1,2,3,4,5"; //字符串
    char *end = NULL;             //剩下的字符
    int res[5] = {0};             //数字数组
    char *p_shift = test_str;     //要解析的字符串

    for (int i = 0; i < 5; i++)
    {
        res[i] = str2i(p_shift, ',', &end); //将字符串转化为整数
        p_shift = end;
    }

    for (int i = 0; i < 5; i++)
    {
        int number = res[i];
        cout << number << endl;
    }
    cout << endl;
}

void test4()
{
    cout << "test4():: ..." << endl;
    cout << endl;
}

/**
 * @brief 将字符串转化为整数
 *
 * @param str 字符串
 * @param split 分割符
 * @param endptr 剩下的字符串
 * @return int 返回整数
 */
int str2i(const char *str, char split, char **endptr)
{
    int ret = 0;
    ret = strtol(str, endptr, 10);
    if (*endptr != NULL)
    {
        if (**endptr == split)
        {
            *endptr += 1;
        }
    }
    return ret;
}