#ifndef IMANAGER_H
#define IMANAGER_H

#include "../entity/Student.h"
#include "../entity/CalCourse.h"

/**
 * @brief 抽象类: 学生管理系统抽象类
 *
 */
class IManager
{
public:
    virtual ~IManager() = default;
    virtual void addStudent(std::shared_ptr<Student> student) = 0;                           //添加一个学生
    virtual void removeStudent(std::shared_ptr<Student> student) = 0;                        //移除一个学生
    virtual std::shared_ptr<std::vector<std::shared_ptr<Student>>> getStudents() = 0;        //获取学生列表
    virtual int count() = 0;                                                                 //获取学生数量
    virtual void display() = 0;                                                              //显示学生信息
    virtual double getSum() = 0;                                                             //获取总成绩
    virtual double getAverage() = 0;                                                         //获取平均成绩
    virtual std::shared_ptr<std::vector<std::shared_ptr<CalCourse>>> getCourseAverage() = 0; //获取课程平均成绩
};

#endif