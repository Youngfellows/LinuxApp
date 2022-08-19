#ifndef GLOBAL_H
#define GLOBAL_H

#include <iostream>
#include <string>
#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

using namespace std;

//常量 - 容器大小
const int MAXLINE = 4096;
const int SIZE = 20;

const char LOGOUT[] = "logout"; //退出
const char EXIT[] = "exit";
const char QUIT[] = "quit";

#endif