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
 * @param para 向线程传递的参数
 * @return void*
 */
void *threadFunction(void *para);

/**
 * @brief 信号处理函数
 *
 * @param sig
 */
void onSignalTerm(int sig);

#endif