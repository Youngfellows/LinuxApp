#include "./include/Sample.h"

/**
 * @brief 1. 向消息队列发送消息
 *
 */
void test1(int argc, char **argv)
{
    cout << "test1():: ..." << endl;
    const char *pathname = "./file/key.msg"; //消息队列文件名
    int msgid;                               //消息队列ID
    key_t key;                               //消息队列键值
    Message msginfo;                         //发送的消息
    key = ftok(pathname, 1);                 //获取键值
    if (key == -1)
    {
        perror("ftok failed 1");
        exit(1);
    }
    msgid = msgget(key, IPC_CREAT | IPC_EXCL | 0644); //创建或者打开消息队列
    if (msgid == -1)
    {
        perror("msgget failed");
        exit(1);
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