#ifndef SAMPLE_H
#define SAMPLE_H

#include "./Global.h"

void test1();
void test2();
void test3();
void test4();

void *threadFunction(void *para);  //线程回调函数
void *threadFunction2(void *para); //线程回调函数

#endif