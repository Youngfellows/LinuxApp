#ifndef SAMPLE_H
#define SAMPLE_H

#include "./Global.h"

void test1();
void test2();
void test3();
void test4();

/**
 * @brief 获取当前时间精确到毫秒
 *
 * @return int64_t
 */
int64_t getTimeMsec();

/**
 * @brief 线程回调函数
 *
 * @param arg 向线程传递的参数
 * @return void*
 */
void *semWaitFunction(void *arg);

/**
 * @brief 线程回调函数
 *
 * @param arg 向线程传递的参数
 * @return void*
 */
void *semTimedWaitFunction(void *arg);

/**
 * @brief 线程回调函数
 * 
 * @param arg 向线程传递的参数
 * @return void* 
 */
void *semPostFunction(void *arg);

#endif