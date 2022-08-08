#ifndef STUDENT_H
#define STUDENT_H

#include "../Global.h"
#include "./Course.h"

/**
 * @brief 实体类: 学生
 *
 */
class Student
{
private:
    std::string name;                                                           //姓名
    int age;                                                                    //年龄
    std::string sex;                                                            //性别
    std::shared_ptr<std::vector<std::shared_ptr<Course>>> courseList = nullptr; //课程列表
    // double sum;                                                                 //总成绩
    // double average;                                                             //平均成绩

public:
    Student(std::string name, int age, std::string sex);
    ~Student();
    std::string getName();                                             //获取姓名
    int getAge();                                                      //获取年龄
    std::string getSex();                                              //获取性别
    void addCourse(std::shared_ptr<Course> course);                    //添加课程
    void removeCourse(std::shared_ptr<Course> course);                 //移除一门课程
    std::shared_ptr<std::vector<std::shared_ptr<Course>>> getCourse(); //获取课程列表
    double getSum();                                                   //获取总成绩
    double getAverage();                                               //获取平均成绩
    void display();                                                    //显示学生信息
};
#endif