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
 * @param para
 * @return void*
 */
void *threadFunction(void *para);

/**
 * @brief 线程清理函数
 *
 * @param arg
 */
void myCleanFunction(void *arg);

#endif