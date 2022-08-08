#ifndef STUDENT_MANAGER_H
#define STUDENT_MANAGER_H

#include "../interface/IManager.h"

/**
 * @brief 学生信息管理系统
 *
 */
class StudentManager : public IManager
{
private:
    std::shared_ptr<std::vector<std::shared_ptr<Student>>> students = nullptr;        //学生列表
    std::shared_ptr<std::vector<std::shared_ptr<CalCourse>>> calCourseList = nullptr; //平均成绩列表

public:
    StudentManager();
    ~StudentManager();
    virtual void addStudent(std::shared_ptr<Student> student) override;                           //添加一个学生
    virtual void removeStudent(std::shared_ptr<Student> student) override;                        //移除一个学生
    virtual std::shared_ptr<std::vector<std::shared_ptr<Student>>> getStudents() override;        //获取学生列表
    virtual int count() override;                                                                 //获取学生数量
    virtual void display() override;                                                              //显示学生信息
    virtual double getSum() override;                                                             //获取总成绩
    virtual double getAverage() override;                                                         //获取平均成绩
    virtual std::shared_ptr<std::vector<std::shared_ptr<CalCourse>>> getCourseAverage() override; //获取课程平均成绩
};

#endif