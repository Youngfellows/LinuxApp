#ifndef SAMPLE_H
#define SAMPLE_H

#include "./Global.h"

void test1();
void test2();
void test3();
void test4();
void mutexVer();
void rdlockVer();

/**
 * @brief 线程回调函数
 *
 * @param para
 * @return void*
 */
void *threadFunctin1(void *para);

/**
 * @brief 线程回调函数
 *
 * @param para
 * @return void*
 */
void *threadFunctin2(void *para);

/**
 * @brief 线程回调函数
 *
 * @param para
 * @return void*
 */
void *threadFunctin3(void *para);

/**
 * @brief 线程回调函数
 *
 * @param para
 * @return void*
 */
void *threadFunctin4(void *para);

#endif