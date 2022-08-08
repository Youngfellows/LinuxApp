#ifndef ICOURSE_CAL_H
#define ICOURSE_CAL_H

#include "../Global.h"

/**
 * @brief 实体类: 统计单一课程分数实体对象
 *
 */
class CalCourse
{
private:
    std::string name; //课程名称
    double sumScore;  //总成绩
    int number;       //数量

public:
    virtual ~CalCourse() = default;
    CalCourse() = default;
    CalCourse(std::string name, double score, int num);
    std::string getName();       //获取课程名称
    double getSum();             //获取总分数
    void setScore(double score); //设置分数
    int getNumber();             //获取课程数量
    void setNumber(int number);  //设置课程数量
    double getAverage();         //获取平均成绩
};
#endif