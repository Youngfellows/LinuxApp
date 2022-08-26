#ifndef SAMPLE_H
#define SAMPLE_H

#include "./Global.h"
#include "./CarInfo.h"

void test1();
void test2();
void test3();
void test4();
void test5();

void *threadFunction1(void *para); //线程1回调函数
void *threadFunction2(void *para); //线程2回调函数
void *threadFunction3(void *para); //线程3回调函数
void *threadFunction4(void *para); //线程4回调函数
void *threadFunction5(void *para); //线程5回调函数
void *threadFunction6(void *para); //线程6回调函数

#endif