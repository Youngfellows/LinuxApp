#include "./include/Sample.h"

/**
 * @brief 解析命令行参数
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    char cmd[MAX_DATA_SIZE]; //命令行参数字符串
    char *cmds[N];           //命令行参数字符串数组

    while (true)
    {
        printf(">");
        bzero(cmd, MAX_DATA_SIZE);
        if (fgets(cmd, MAX_DATA_SIZE, stdin) == nullptr) //输入命令行参数
        {
            printf("fgets error!\n");
            return;
        }
        // printf("%s", cmd);
        cmd[strlen(cmd) - 1] = '\0';   //字符串结束
        int number = parse(cmd, cmds); //解析命令行参数
        for (int i = 0; i < number; i++)
        {
            char *tcmd = cmds[i];
            printf("%d:%s\n", i, tcmd);
        }
    }

    cout << endl;
}

/**
 * @brief 解析命令行参数
 *
 * @param buf 命令行参数
 * @param args 命令行参数字符串数组
 * @return int 返回命令行参数字符串数组长度
 */
int parse(char *buf, char **args)
{
    int num = 0;
    while (*buf != '\0')
    {
        // printf("0,%d:%s\n", num, buf);
        while ((*buf == ' ') || (*buf == '\t') || (*buf == '\n'))
        {
            *buf++ = '\0';
        }
        *args++ = buf;
        ++num;
        // printf("1,%d:%s\n", num, buf);
        while ((*buf != '\0') && (*buf != ' ') && (*buf != '\t') && (*buf != '\n'))
        {
            buf++;
        }
        // printf("2,%d:%s\n", num, buf);
    }
    //*args = '\0';
    return num;
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