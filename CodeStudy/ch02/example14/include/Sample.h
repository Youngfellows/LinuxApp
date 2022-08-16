#ifndef SAMPLE_H
#define SAMPLE_H

#include "./Global.h"

void test1();
void test2(int argc, char *argv[]);
void test3();
void test4();
int checkFileType(char *pathname);
int copyDir(char *fromDirName, char *toDirName);
int copyRegularFile(char *fromPathName, char *toPathName);
int copyLinkFile(char *fromPathName, char *toPathName);
#endif