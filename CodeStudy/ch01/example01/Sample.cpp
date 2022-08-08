#include "./include/Sample.h"

void test1()
{
    cout << "test1():: ..." << endl;
    //学生信息管理系统
    std::shared_ptr<IManager> manager = std::make_shared<StudentManager>(); //学生信息管理系统
    std::shared_ptr<Student> stu1 = std::make_shared<Student>("杨过", 22, "男");
    std::shared_ptr<Student> stu2 = std::make_shared<Student>("小龙女", 18, "女");
    std::shared_ptr<Student> stu3 = std::make_shared<Student>("谢晓峰", 30, "男");
    std::shared_ptr<Student> stu4 = std::make_shared<Student>("慕容秋荻", 24, "女");

    //添加课程
    std::shared_ptr<Course> stu1Course1 = std::make_shared<Course>("语文", 88.5);
    std::shared_ptr<Course> stu1Course2 = std::make_shared<Course>("数学", 92.0);
    std::shared_ptr<Course> stu1Course3 = std::make_shared<Course>("英语", 94.0);
    std::shared_ptr<Course> stu1Course4 = std::make_shared<Course>("物理", 98.5);
    std::shared_ptr<Course> stu1Course5 = std::make_shared<Course>("化学", 86.0);

    std::shared_ptr<Course> stu2Course1 = std::make_shared<Course>("语文", 88.5);
    std::shared_ptr<Course> stu2Course2 = std::make_shared<Course>("数学", 92.0);
    std::shared_ptr<Course> stu2Course3 = std::make_shared<Course>("英语", 94.0);
    std::shared_ptr<Course> stu2Course4 = std::make_shared<Course>("物理", 98.5);
    std::shared_ptr<Course> stu2Course5 = std::make_shared<Course>("化学", 86.0);

    std::shared_ptr<Course> stu3Course1 = std::make_shared<Course>("语文", 88.5);
    std::shared_ptr<Course> stu3Course2 = std::make_shared<Course>("数学", 92.0);
    std::shared_ptr<Course> stu3Course3 = std::make_shared<Course>("英语", 94.0);
    std::shared_ptr<Course> stu3Course4 = std::make_shared<Course>("物理", 98.5);
    std::shared_ptr<Course> stu3Course5 = std::make_shared<Course>("化学", 86.0);

    std::shared_ptr<Course> stu4Course1 = std::make_shared<Course>("语文", 88.5);
    std::shared_ptr<Course> stu4Course2 = std::make_shared<Course>("数学", 92.0);
    std::shared_ptr<Course> stu4Course3 = std::make_shared<Course>("英语", 94.0);
    std::shared_ptr<Course> stu4Course4 = std::make_shared<Course>("物理", 98.5);
    std::shared_ptr<Course> stu4Course5 = std::make_shared<Course>("化学", 86.0);

    stu1->addCourse(stu1Course1);
    stu1->addCourse(stu1Course2);
    stu1->addCourse(stu1Course3);
    stu1->addCourse(stu1Course4);
    stu1->addCourse(stu1Course5);

    stu2->addCourse(stu2Course1);
    stu2->addCourse(stu2Course2);
    stu2->addCourse(stu2Course3);
    stu2->addCourse(stu2Course4);
    stu2->addCourse(stu2Course5);

    stu3->addCourse(stu3Course1);
    stu3->addCourse(stu3Course2);
    stu3->addCourse(stu3Course3);
    stu3->addCourse(stu3Course4);
    stu3->addCourse(stu3Course5);

    stu4->addCourse(stu4Course1);
    stu4->addCourse(stu4Course2);
    stu4->addCourse(stu4Course3);
    stu4->addCourse(stu4Course4);
    stu4->addCourse(stu4Course5);

    manager->addStudent(stu1);
    manager->addStudent(stu2);
    manager->addStudent(stu3);
    manager->addStudent(stu4);

    double sum = manager->getSum();                   //总成绩
    double average = manager->getAverage();           //平均成绩
    int size = manager->count();                      //学生数量
    auto courseAverage = manager->getCourseAverage(); //课程平均成绩
    cout << "总成绩:" << sum << ",平均成绩:" << average << ",学生数量:" << size << endl;
    manager->display();

    cout << endl;
}

void test2()
{
    cout << "test2():: ..." << endl;
    cout << endl;
}

void test3()
{
    cout << "test3():: ..." << endl;
    cout << endl;
}

void test4()
{
    cout << "test4():: ..." << endl;
    cout << endl;
}