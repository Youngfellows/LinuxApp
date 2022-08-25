#include "./include/Sample.h"

/**
 * @brief 向线程传递结构体参数
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    pthread_t tid;        //线程id
    int ret;              //线程创建结果
    Content data;         //结构体参数
    char cache[MAX_SIZE]; //缓冲区
    printf("请输入次数:");
    scanf("%d", &data.number);
    getchar(); //消耗掉一个回车
    printf("请输入内容:");
    fgets(cache, sizeof(cache), stdin);
    // fputs(cache, stdout);
    strcpy(data.content, cache);
    // fputs(data.content, stdout);
    ret = pthread_create(&tid, nullptr, threadProcess, (void *)&data); //创建线程
    if (ret != 0)
    {
        perror("pthread_create error");
        exit(0);
    }
    pthread_join(tid, nullptr); //等待子线程结束
    cout << endl;
    exit(0);
}

/**
 * @brief 线程回调函数
 *
 * @param content 向线程传递的结构体指针变量
 * @return void*
 */
void *threadProcess(void *para)
{
    Content *content = (Content *)para;
    printf("number:%d,content:%s\n", content->number, content->content);
    while (content->number--)
    {
        fputs(content->content, stdout); //打印字符串
    }
    pthread_exit(0); //子线程结束
    // return nullptr;
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