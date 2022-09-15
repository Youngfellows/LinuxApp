#ifndef SAMPLE_H
#define SAMPLE_H

#include "./Global.h"

void test1();
void test2();
void test3();
void test4();

/**
 * @brief 信号处理函数
 *
 * @param sig 信号
 */
void signalHandler(int sig);

/**
 * @brief 写入到文件
 *
 */
void writeToFile();

#endif