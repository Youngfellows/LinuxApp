#include "../../include/entity/CalCourse.h"

CalCourse::CalCourse(std::string name, double score, int num)
{
    this->name = name;
    this->sumScore = score;
    this->number = num;
}

std::string CalCourse::getName()
{
    return this->name;
}

double CalCourse::getSum()
{
    return this->sumScore;
}

void CalCourse::setScore(double score)
{
    this->sumScore = score;
}

int CalCourse::getNumber()
{
    return this->number;
}

void CalCourse::setNumber(int number)
{
    this->number = number;
}

double CalCourse::getAverage()
{
    return this->sumScore / this->number;
}