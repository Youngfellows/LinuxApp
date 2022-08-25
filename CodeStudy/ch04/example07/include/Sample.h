#ifndef SAMPLE_H
#define SAMPLE_H

#include "./Global.h"

void test1();
void test2();
void test3();
void test4();

void *threadFunction1(void *para); //线程1回调函数
void *threadFunction2(void *para); //线程2回调函数

#endif