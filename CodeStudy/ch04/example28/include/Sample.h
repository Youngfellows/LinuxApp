#ifndef SAMPLE_H
#define SAMPLE_H

#include "./Global.h"

void test1();
void test2();
void test3();
void test4();

/**
 * @brief 生产者线程
 *
 * @param para 向线程传递的参数
 * @return void*
 */
void *threadProducer(void *para);

/**
 * @brief 消费者线程
 *
 * @param para 向线程传递的参数
 * @return void*
 */
void *threadConsumer(void *para);

#endif