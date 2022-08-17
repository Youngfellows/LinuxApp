#include "./include/Sample.h"

/**
 * @brief 循环输入命令行参数,并解析为字符串数组
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    char buffer[MAXLINE]; //输入缓冲区
    char *rt;             //每次输入的结果
    char *args[64];       //字符串数组
    int argNum = 0;       //字符串数组大小

    //循环输入字符串,并解析命令行参数
    while (true)
    {
        printf("%%");
        rt = fgets(buffer, MAXLINE, stdin); //输入带空格的字符串
        if (rt == nullptr)
        {
            printf("fgets error\n");
            exit(1); //退出进程
        }
        //假如是输入的是enter,则继续提示输入
        // if (strcmp(buffer, "\n") == 0)
        if (!strcmp(buffer, "\n"))
        {
            // printf("%%");
            continue;
        }
        printf("%ld,%s\n", strlen(buffer), buffer);
        if (buffer[strlen(buffer) - 1] == '\n') //最后一个是enter字符
        {
            buffer[strlen(buffer) - 1] = 0; //最后一个作为字符串结束标志
        }
        printf("%ld,%s\n", strlen(buffer), buffer);

        printf("args=%p\n", args);
        //解析输入的字符串为字符串列表
        argNum = parse(buffer, args);
        printf("argNum=%d\n", argNum);
        //遍历解析后的列表
        // for (int i = 0; i < argNum; i++)
        // {
        //     char *arg = args[i];
        //     printf("%s\n", arg);
        // }
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

/**
 * @brief 解析命令行参数
 *
 * @param originBuff 输入的字符串
 * @param args 返回字符串数组
 * @return int 返回数组的大小
 */
int parse(char *originBuff, char **args)
{
    printf("1,args=%p\n", args);
    int len = strlen(originBuff);
    char temp[len]; //拷贝原始字符串
    char *buffer = temp;
    strcpy(buffer, originBuff); //拷贝原始字符串
    // char buf[len];              //临时缓冲区

    int number = 0;         //参数列表个数
    int start = 0;          //字符开始的索引
    int end = 0;            //字符结束的索引
    while (*buffer != '\0') //字符串没有结束
    {
        printf("start:%d,end:%d\n", start, end);
        while ((*buffer == ' ') || (*buffer == '\t') || (*buffer == '\n'))
        {
            *buffer++ = '\0'; //该循环是定位到命令中每个字符串的第一个非空字符串
            printf("1,%s\n", buffer);
            end++;
            printf("1,start:%d,end:%d\n", start, end);

            int size = end - start;
            printf("1,size:%d\n", size);
            if ((size > 0) && ((originBuff[start] != '\0') && (originBuff[start] != ' ') && (originBuff[start] != '\t') && (originBuff[start] != '\n')))
            {
                char buf[size];                         //临时缓冲区
                memset(buf, 0, sizeof(buf));            //清空缓存
                strncpy(buf, originBuff + start, size); //拷贝字符串
                buf[size - 1] = '\0';
                printf("%s\n", buf);
                printf("args=%p\n", args);
                //*args++ = buf; //找到非空字符串依次赋值给args[i]
                // strcpy(*args++, buf); //找到非空字符串依次赋值给args[i]
                // memcpy(args[number], buf, size);
                printf("args[%d]=%s\n", number, args[number]);
                ++number;
            }
            start = end;
        }

        //正常的字符就往后移动,直到定位到非空字符后面的第一个空格
        while ((*buffer != '\0') && (*buffer != ' ') && (*buffer != '\t') && (*buffer != '\n'))
        {
            buffer++;
            end++;
        }
    }

    printf("2,start:%d,end:%d\n", start, end);
    int size = end - start;
    printf("2,size:%d\n", size);
    if ((size > 0) && ((originBuff[start] != '\0') && (originBuff[start] != ' ') && (originBuff[start] != '\t') && (originBuff[start] != '\n')))
    {
        char buf[size];              //临时缓冲区
        memset(buf, 0, sizeof(buf)); //清空缓存
        strncpy(buf, originBuff + start, size);
        buf[size] = '\0';
        printf("%s\n", buf);
        //*args++ = buf; //找到非空字符串依次赋值给args[i]
        // strcpy(*args++, buf); //找到非空字符串依次赋值给args[i]
        // printf("args[%d]=%s\n", number, args[number]);
        number++;
    }
    return number;
}