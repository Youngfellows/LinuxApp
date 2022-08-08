#include "../../include/entity/Course.h"

Course::Course(std::string name, double score)
{
    //cout << "Course()构造函数" << endl;
    this->cName = name;
    this->score = score;
}

Course::~Course()
{
    //cout << "~Course()析构函数" << endl;
}

std::string Course::getCName()
{
    return this->cName;
}

double Course::getScore()
{
    return this->score;
}
