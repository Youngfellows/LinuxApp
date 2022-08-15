#ifndef SAMPLE_H
#define SAMPLE_H

#include "./Global.h"

void test1(int argc, char *argv[]);
void test2(int argc, char *argv[]);
void test3();
void test4();
int checkFileType(char *pathname);
void copyDir(char *fromDirName, char *toDirName, bool isCreateRoot);

#endif