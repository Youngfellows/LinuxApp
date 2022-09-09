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
    MyTask *task = new MyTask(); //创建对象
    char data[] = "明天就是中秋啦\n";
    task->setData((void *)data);                                               //设置要向线程传递的数据
    std::shared_ptr<ThreadPool> threadPool = std::make_shared<ThreadPool>(10); //创建线程池
    for (int i = 0; i < 10; i++)
    {
        threadPool->addTask(task);
    }

    while (true)
    {
        printf("仍然需要%d个任务进行处理\n", threadPool->getTaskSize());
        //任务队列没有任务了
        if (threadPool->getTaskSize() == 0)
        {
            //清除线程池
            if (threadPool->stopAll() == -1)
            {
                printf("线程已经清除,退出线程池\n");
                exit(0); //结束进程
            }
        }
        sleep(2); //休眠2秒
        printf("2秒以后 ...\n");
    }

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