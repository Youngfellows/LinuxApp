#ifndef SAMPLE_H
#define SAMPLE_H

#include "./Global.h"

void test1();
void test2();
void test3();
void test4();

/**
 * @brief 线程回调函数
 *
 * @param name 姓名
 * @param age 年龄
 * @param salary 工资
 */
void threadFunction(char *name, int age, double *salary);

#endif