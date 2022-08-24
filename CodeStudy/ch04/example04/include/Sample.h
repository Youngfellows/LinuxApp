#ifndef SAMPLE_H
#define SAMPLE_H

#include "./Global.h"

void test1();
void test2();
void test3();
void test4();

void *reader(void *tid); //线程回调函数,读文件
void *writer(void *tid); //线程回调函数,写文件
void readFile(int tid);  //读文件
void writeFile(int tid); //写文件
void randomSleep();      //随机休眠

#endif