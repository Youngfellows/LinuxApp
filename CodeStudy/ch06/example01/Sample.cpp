#include "./include/Sample.h"

/**
 * @brief 1. 测试任务类是否可用
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    std::string taskName = "测试线程";
    std::shared_ptr<Task> task = std::make_shared<MyTask>(taskName); //创建任务
    const char *message = "今天天气很不错,适合出去看风景 ...";
    task->setData((void *)message);
    task->run();

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