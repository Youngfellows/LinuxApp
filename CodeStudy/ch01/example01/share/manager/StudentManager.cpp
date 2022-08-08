#include "../../include/manager/StudentManager.h"

StudentManager::StudentManager()
{
    cout << "StudentManager()构造函数" << endl;
    this->students = std::make_shared<std::vector<std::shared_ptr<Student>>>();
    this->calCourseList = std::make_shared<std::vector<std::shared_ptr<CalCourse>>>();
}

StudentManager::~StudentManager()
{
    cout << "~StudentManager()析构函数" << endl;
}

void StudentManager::addStudent(std::shared_ptr<Student> student)
{
    // cout << "StudentManager::addStudent():: start ..." << endl;
    this->students->push_back(student);
    // cout << "StudentManager::addStudent():: end ..." << endl;
}

void StudentManager::removeStudent(std::shared_ptr<Student> student)
{
    auto iter = std::find(this->students->begin(), this->students->end(), student);
    if (iter != this->students->end())
    {
        this->students->erase(iter);
    }
    else
    {
        cout << "StudentManager::removeStudent():: 不存在学生," << student->getName() << ",无需删除 ..." << endl;
    }
}

std::shared_ptr<std::vector<std::shared_ptr<Student>>> StudentManager::getStudents()
{
    return this->students;
}

int StudentManager::count()
{
    return this->students->size();
}

void StudentManager::display()
{
    cout << "StudentManager::display():: ..." << endl;
    //先显示各个学生信息
    if (!this->students->empty())
    {
        for (auto iter = this->students->begin(); iter != this->students->end(); iter++)
        {
            auto student = (*iter);
            student->display();
        }
    }

    //再显示每个科目信息
    std::shared_ptr<std::vector<std::shared_ptr<CalCourse>>> calCourses = this->getCourseAverage();
    if (!calCourses->empty())
    {
        for (auto iter = calCourses->begin(); iter != calCourses->end(); iter++)
        {
            auto calCourse = *iter;
            std::string cName = calCourse->getName();
            double average = calCourse->getAverage();
            cout << "课程:" << cName << ",平均成绩:" << average << endl;
        }
    }
}

double StudentManager::getSum()
{
    double sum = 0;
    for (auto iter = this->students->begin(); iter != this->students->end(); iter++)
    {
        sum += (*iter)->getSum();
    }
    return sum;
}

double StudentManager::getAverage()
{
    double sum = 0;
    for (auto iter = this->students->begin(); iter != this->students->end(); iter++)
    {
        sum += (*iter)->getSum();
    }
    double average = 0;
    if (this->count() > 0)
    {
        average = sum / this->count();
    }
    return average;
}

std::shared_ptr<std::vector<std::shared_ptr<CalCourse>>> StudentManager::getCourseAverage()
{
    // cout << "StudentManager::getCourseAverage():: ..." << endl;
    for (auto iter = this->students->begin(); iter != this->students->end(); iter++)
    {
        auto student = (*iter);
        auto courses = student->getCourse();
        for (auto course : *courses)
        {
            std::string cName = course->getCName();
            double score = course->getScore();
            // cout << "StudentManager::getCourseAverage():: 学生:" << student->getName() << ",课程:" << cName << ",分数:" << score << endl;
            if (!calCourseList->empty())
            {
                // cout << "ssssssssssssssssss,size:" << calCourseList->size() << endl;
                bool exist = false; //是否存在
                for (auto calCourse : *calCourseList)
                {
                    // cout << "xxxxxxxxxxxxxxxxx,calCourse:" << calCourse << endl;
                    if (calCourse != nullptr)
                    {
                        std::string name = calCourse->getName();
                        // cout << "StudentManager::getCourseAverage():: cName:" << cName << ",name:" << name << endl;
                        if (cName.compare(name) == 0)
                        {
                            // cout << "StudentManager::getCourseAverage():: 1,update ..." << endl;
                            //已经存在,更新课程信息
                            double sum = calCourse->getSum();
                            int num = calCourse->getNumber();
                            // cout << "StudentManager::getCourseAverage():: 1,sum:" << sum << ",num:" << num << endl;
                            calCourse->setScore(sum + score); //更新成绩
                            calCourse->setNumber(num + 1);    //更新课程数量
                            // cout << "StudentManager::getCourseAverage():: 2,update cName:" << cName << endl;
                            exist = true;
                            break;
                        }
                    }
                    // cout << "yyyyyyyyyyyyy" << endl;
                }

                if (!exist)
                {
                    //不存在,添加到容器列表
                    // cout << "StudentManager::getCourseAverage():: 1,add ..." << endl;
                    std::shared_ptr<CalCourse> calCourse = std::make_shared<CalCourse>(cName, score, 1);
                    calCourseList->push_back(calCourse);
                    // cout << "StudentManager::getCourseAverage():: 2,add,cName:" << cName << endl;
                }
            }
            else
            {
                //不存在,添加到容器列表
                std::shared_ptr<CalCourse> calCourse = std::make_shared<CalCourse>(cName, score, 1);
                calCourseList->push_back(calCourse);
                // cout << "StudentManager::getCourseAverage():: 0,add cName:" << cName << endl;
            }
        }
        cout << endl;
    }
    return this->calCourseList;
}