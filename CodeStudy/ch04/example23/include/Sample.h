#ifndef SAMPLE_H
#define SAMPLE_H

#include "./Global.h"

void test1();
void test2();
void test3();
void test4();

/**
 * @brief 线程1回调函数
 *
 * @param para 向线程传递的参数
 * @return void*
 */
void *threadFunction1(void *para);

/**
 * @brief 线程2回调函数
 *
 * @param para 向线程传递的参数
 * @return void*
 */
void *threadFunction2(void *para);

#endif