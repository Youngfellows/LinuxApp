#ifndef SAMPLE_H
#define SAMPLE_H

#include "./Global.h"

void test1();
void test2();
void test3();
void test4();

/**
 * @brief 卖货线程
 *
 * @param para
 * @return void*
 */
void *threadSellGoods(void *para);

/**
 * @brief 对账线程
 *
 * @param para
 * @return void*
 */
void *threadReconciliation(void *para);

#endif