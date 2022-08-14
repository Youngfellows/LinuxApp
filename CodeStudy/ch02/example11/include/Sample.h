#ifndef SAMPLE_H
#define SAMPLE_H

#include "./Global.h"

void test1(int argc, char *argv[]);
void test2();
void test3();
void test4();
void lsdir(char *pathname, int flag);
int checkFileType(char *pathname);
void displayProperties(char *pathname);
void displaySize(struct stat *statbuf);
void displayDate(struct stat *statbuf);

#endif