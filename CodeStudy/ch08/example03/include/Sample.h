#ifndef SAMPLE_H
#define SAMPLE_H

#include "./Global.h"
#include "./Semun.h"

void test1();
void test2();
void test3();
void test4();

int P(int semid, int semnum);

int V(int semid, int semnum);

#endif