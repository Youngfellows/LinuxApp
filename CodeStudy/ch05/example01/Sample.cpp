#include "./include/Sample.h"

/**
 * @brief 1. 批量创建线程,线程数组
 *
 */
void test1()
{
    cout << "test1():: ..." << endl;
    std::thread threads[THREAD_NUMBER]; //批量定义5个thread对象,但此时并不会执行线程
    cout << "开始创建" << THREAD_NUMBER << "个线程" << endl;
    for (int i = 0; i < THREAD_NUMBER; i++)
    {
        threads[i] = std::thread(threadFunction, i + 1); //这里开始执行线程函数threadFunction
    }
    //等待每个线程结束
    for (auto &t : threads)
    {
        t.join();
    }
    cout << "全部线程都执行完成了 ..." << endl;
    cout << endl;
}

/**
 * @brief 线程回调函数
 *
 * @param number
 */
void threadFunction(int number)
{
    std::cout << "threadFunction:: number=" << number << endl;
}

/**
 * @brief 2. 创建线程,不传递参数
 *
 */
void test2()
{
    cout << "test2():: ..." << endl;
    std::thread myThread(threadFunction1); //定义线程对象,并把线程线程函数指针传入
    // sleep(3);                              // main线程挂起1秒,为了让子线程执行
    myThread.join(); //等待子线程执行完成
    cout << "主线程执行完成了 ..." << endl;
    cout << endl;
}

/**
 * @brief 线程函数没有参数
 *
 */
void threadFunction1()
{
    cout << "C++11的线程函数,开始执行了 ..." << endl;
    // sleep(2); //子线程休眠2秒
    cout << "C++11的线程函数,执行完成了 ..." << endl;
}

/**
 * @brief 3. 创建线程,向线程传递一个整数
 *
 */
void test3()
{
    cout << "test3():: ..." << endl;
    std::thread myThread(threadFuniction2, 1024); //定义线程对象,并把线程函数指针和线程参数传入
    myThread.join();                              //等待子线程结束运行
    cout << "主线程结束运行 ..." << endl;
    cout << endl;
}

/**
 * @brief 线程回调函数
 *
 * @param number 向线程传递的参数
 */
void threadFuniction2(int number)
{
    cout << "子线程接收到的参数是:" << number << endl;
}

/**
 * @brief 4. 创建线程,并向线程传递字符串参数
 *
 */
void test4()
{
    cout << "test4():: ..." << endl;
    std::string message = "今天天气真的很不错,适合出去玩 ...";
    std::thread myThread(threadFunction3, message); //定义线程对象,并把线程函数指针和线程参数传入
    myThread.join();                                //等待子线程结束执行
    cout << "主线程结束运行" << endl;
    cout << endl;
}

/**
 * @brief 线程回调函数
 *
 * @param message 向线程传递的参数
 */
void threadFunction3(std::string message)
{
    cout << "子线程接收到主线程传递过来的字符串: " << message << endl;
}

/**
 * @brief 5. 创建线程,并向线程传递字符串参数
 *
 */
void test5()
{
    cout << "test5():: ..." << endl;
    // std::string text = "今天大太阳,适合晒晒被子 ...";
    char *message = "今天大太阳,适合晒晒被子 ...";
    std::thread myThread(threadFunction4, message); //定义线程对象,并把线程函数指针和线程参数传入
    myThread.join();                                //等待子线程结束
    cout << "主线程结束了 ..." << endl;
    cout << endl;
}

/**
 * @brief 线程回调函数
 *
 * @param message 主线程向子线程传递的参数
 */
void threadFunction4(char *message)
{
    cout << "子线程接收到主线程传递的字符串: " << message << endl;
}

/**
 * @brief 6. 创建线程,向子线程传递结构体指针变量
 *
 */
void test6()
{
    cout << "test6():: ..." << endl;
    CarInfo carInfo; //结构体变量
    carInfo.serialNum = 1234567890;
    carInfo.brand = "JEEP";
    // std::shared_ptr<CarInfo> car(&carInfo);     //普通指针转化为智能指针
    std::thread myThread(threadFunction5, &carInfo); //定义线程对象,并把线程函数指针和线程参数传入
    myThread.join();                                 //等待子线程结束
    cout << "主线程执行完成 ..." << endl;
    cout << endl;
}

/**
 * @brief 线程回调函数
 *
 * @param carInfo 主线程向子线程传递的结构体参数
 */
void threadFunction5(CarInfo *carInfo)
{
    cout << "子线程接收到,车品牌:" << carInfo->brand << ",序列号:" << carInfo->serialNum << endl;
}

/**
 * @brief 7. 创建线程,向线程传递多个参数
 *
 */
void test7()
{
    cout << "test7():: ..." << endl;
    CarInfo carInfo;
    carInfo.brand = "比亚迪-汉";
    carInfo.serialNum = 9876543210;
    std::string name = "张无忌";
    int age = 22;
    double salary = 26000;
    std::thread myThread(threadFunction6, name, age, salary, &carInfo); //定义线程对象,并把线程函数指针和线程参数传入
    myThread.join();                                                    //等待子线程结束
    cout << "主线程结束运行了 ..." << endl;
    cout << endl;
}

/**
 * @brief 线程回调函数
 *
 * @param name 姓名
 * @param age 年龄
 * @param salary 工资
 * @param carInfo 车辆
 */
void threadFunction6(std::string name, int age, double salary, CarInfo *carInfo)
{
    cout << "姓名:" << name << endl;
    cout << "年龄:" << age << endl;
    cout << "工资:" << salary << endl;
    cout << "车品牌:" << carInfo->brand << endl;
    cout << "车牌号:" << carInfo->serialNum << endl;
}

/**
 * @brief 8. 通过移动构造函数来启动线程
 *
 */
void test8()
{
    cout << "test8():: ..." << endl;
    int number = 11;
    cout << "主线程:1,number=" << number << endl;
    std::thread thread1(threadFunction7, ref(number)); // ref(number)是number的引用
    std::thread thread2(move(thread1));                // thread2执行threadFunction7,thread1不上thread对象
    thread2.join();                                    //等待thread2线程执行完成
    cout << "主线程执行完:2,number=" << number << endl;
    cout << endl;
}

/**
 * @brief 线程回调函数
 *
 * @param number
 */
void threadFunction7(int &number)
{
    cout << "threadFunction7:: number=" << number << endl;
    number += 22;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000)); //休眠1秒=1000毫秒
}

void test9()
{
    cout << "test9():: ..." << endl;
    cout << endl;
}

void test10()
{
    cout << "test10():: ..." << endl;
    cout << endl;
}

void test11()
{
    cout << "test11():: ..." << endl;
    cout << endl;
}

void test12()
{
    cout << "test12():: ..." << endl;
    cout << endl;
}

void test13()
{
    cout << "test13():: ..." << endl;
    cout << endl;
}

void test14()
{
    cout << "test14():: ..." << endl;
    cout << endl;
}

void test15()
{
    cout << "test15():: ..." << endl;
    cout << endl;
}

void test16()
{
    cout << "test16():: ..." << endl;
    cout << endl;
}

void test17()
{
    cout << "test17():: ..." << endl;
    cout << endl;
}

void test18()
{
    cout << "test18():: ..." << endl;
    cout << endl;
}

void test19()
{
    cout << "test19():: ..." << endl;
    cout << endl;
}

void test20()
{
    cout << "test20():: ..." << endl;
    cout << endl;
}
