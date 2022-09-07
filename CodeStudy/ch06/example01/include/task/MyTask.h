#ifndef MY_TASK_H
#define MY_TASK_H

#include "../Task.h"

/**
 * @brief 派生类: 具体的任务类
 *
 */
class MyTask : public Task
{
private:
public:
    MyTask() = default;
    MyTask(std::string &taskName);
    ~MyTask();
    virtual int run() override; //实现父类的接口
};

#endif