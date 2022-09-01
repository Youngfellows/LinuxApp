#ifndef SAMPLE_H
#define SAMPLE_H

#include "./Global.h"
#include "./CarInfo.h"

void test1();
void test2();
void test3();
void test4();
void test5();
void test6();
void test7();
void test8();
void test9();
void test10();
void test11();
void test12();
void test13();
void test14();
void test15();
void test16();
void test17();
void test18();
void test19();
void test20();

/**
 * @brief 线程回调函数
 *
 * @param number
 */
void threadFunction(int number);

/**
 * @brief 线程函数没有参数
 *
 */
void threadFunction1();

/**
 * @brief 线程回调函数
 *
 * @param number 向线程传递的参数
 */
void threadFuniction2(int number);

/**
 * @brief 线程回调函数
 *
 * @param message 向线程传递的参数
 */
void threadFunction3(std::string message);

/**
 * @brief 线程回调函数
 *
 * @param message 主线程向子线程传递的参数
 */
void threadFunction4(char *message);

/**
 * @brief 线程回调函数
 *
 * @param carInfo 主线程向子线程传递的结构体参数
 */
void threadFunction5(CarInfo *carInfo);

/**
 * @brief 线程回调函数
 *
 * @param name 姓名
 * @param age 年龄
 * @param salary 工资
 * @param carInfo 车辆
 */
void threadFunction6(std::string name, int age, double salary, CarInfo *carInfo);

/**
 * @brief 线程回调函数
 *
 * @param number
 */
void threadFunction7(int &number);

#endif