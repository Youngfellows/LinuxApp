#ifndef TASK_H
#define TASK_H

#include "./Global.h"

/**
 * @brief 执行任务的类: 设置任务数据并执行
 *
 */
class Task
{
protected:
    std::string mTaskName; //任务的名称
    void *mPtrData;        //要执行的任务的具体数据,向线程传递的数据

public:
    Task() = default; //默认构造函数
    Task(std::string &taskName);
    virtual ~Task(); //析构函数,虚函数

    /**
     * @brief 纯虚函数
     * @brief 任务执行函数
     *
     * @return int 执行任务的返回结果
     */
    virtual int run() = 0;

    /**
     * @brief 向线程任务设置数据
     *
     * @param data 要设置的任务数据
     */
    void setData(void *data);
};

#endif