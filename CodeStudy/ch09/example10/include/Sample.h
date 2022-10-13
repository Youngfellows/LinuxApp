#ifndef SAMPLE_H
#define SAMPLE_H

#include "./Global.h"

void test1();
void test2();
void test3();
void test4();

/**
 * @brief 解析命令行参数
 *
 * @param buf 命令行参数
 * @param args 命令行参数字符串数组
 * @return int 返回命令行参数字符串数组长度
 */
int parse(char *buf, char **args);

#endif