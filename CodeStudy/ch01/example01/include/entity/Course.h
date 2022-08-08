#ifndef COURSE_H
#define COURSE_H

#include "../Global.h"

/**
 * @brief 实体类: 课程
 *
 */
class Course
{
private:
    std::string cName; //课程名称
    double score;      //分数

public:
    Course(std::string name, double score);
    ~Course();
    std::string getCName();
    double getScore();
};
#endif