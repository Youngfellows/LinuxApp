#ifndef SAMPLE_H
#define SAMPLE_H

#include "./Global.h"

void test1();
void test2();
void test3();
void test4();

/**
 * @brief 线程回调函数
 * @brief 生产者线程
 * @param arg
 * @return void*
 */
void *producerFunction(void *arg);

/**
 * @brief 线程回调函数
 * @brief 消费者线程
 * @param arg
 * @return void*
 */
void *consumerFunction(void *arg);

/**
 * @brief 初始化信号量
 *
 */
void initSems();

/**
 * @brief 销毁信号量
 *
 */
void destroySems();

#endif