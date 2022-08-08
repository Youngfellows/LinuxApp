#include "../../include/entity/Student.h"

Student::Student(std::string name, int age, std::string sex)
{
    // cout << "Student()构造函数" << endl;
    this->name = name;
    this->age = age;
    this->sex = sex;
    this->courseList = std::make_shared<std::vector<std::shared_ptr<Course>>>();
}

Student::~Student()
{
    // cout << "~Student()析构函数" << endl;
    this->courseList->clear();
}

std::string Student::getName()
{
    return this->name;
}

int Student::getAge()
{
    return this->age;
}

std::string Student::getSex()
{
    return this->sex;
}

void Student::addCourse(std::shared_ptr<Course> course) //添加课程
{
    // cout << "Student::addCourse():: start ..." << endl;
    this->courseList->push_back(course);
    // cout << "Student::addCourse():: end ..." << endl;
}

void Student::removeCourse(std::shared_ptr<Course> course) //移除一门课程
{
    //查找元素是否存在
    auto iter = std::find(this->courseList->begin(), this->courseList->end(), course);
    if (iter != this->courseList->end())
    {
        cout << "Student::removeCourse():: 课程:" << course->getCName() << ",分数:" << course->getScore() << ",移除课程 ..." << endl;
        this->courseList->erase(iter);
    }
    else
    {
        cout << "Student::removeCourse():: 课程:" << course->getCName() << ",分数:" << course->getScore() << ",不存在 ..." << endl;
    }
}

std::shared_ptr<std::vector<std::shared_ptr<Course>>> Student::getCourse()
{
    return this->courseList;
}

double Student::getSum() //获取总成绩
{
    double sum = 0;
    for (auto iter : (*this->courseList))
    {
        sum += iter->getScore();
    }
    return sum;
}

double Student::getAverage() //获取平均成绩
{
    double sum = 0;
    for (auto iter = this->courseList->begin(); iter != this->courseList->end(); iter++)
    {
        sum += (*iter)->getScore();
    }
    double average = 0;
    int size = this->courseList->size();
    if (size > 0)
    {
        average = sum / size;
    }
    return average;
}

void Student::display() //显示学生信息
{
    cout << "Student::display():: 学生:" << this->name << ",性别:" << this->sex << ",年龄:" << this->age << endl;
    for (auto iter : (*this->courseList))
    {
        cout << "课程:" << iter->getCName() << ",分数:" << iter->getScore() << endl;
    }
    //cout << endl;
}
