#include "../include/Task.h"

Task::Task(std::string &taskName)
{
    // cout << __FUNCTION__ << ", 构造函数 ..." << endl;
    this->mTaskName = taskName;
    this->mPtrData = nullptr;
}

Task::~Task()
{
    // cout << __FUNCTION__ << ", 析构函数 ..." << endl;
}

/**
 * @brief 向线程任务设置数据
 *
 * @param data 要设置的任务数据
 */
void Task::setData(void *data)
{
    this->mPtrData = data;
}
