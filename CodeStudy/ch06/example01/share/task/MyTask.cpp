#include "../../include/task/MyTask.h"

MyTask::MyTask(std::string &taskName) : Task(taskName)
{
    cout << __FUNCTION__ << " ,构造函数" << endl;
    srand(time(nullptr)); //获取当前系统时间,设置随机数的种子
}

MyTask::~MyTask()
{
    cout << __FUNCTION__ << " ,析构函数" << endl;
}

int MyTask::run()
{
    cout << __FUNCTION__ << " 运行了 ..." << endl;
    char *message = (char *)mPtrData;
    printf("%s\n", message);
    int wait = rand() % 4 + 1; //产生随机数 1 ~ 5
    printf("wait:%d\n", wait);
    sleep(wait); //挂起wait秒
    return 0;
}