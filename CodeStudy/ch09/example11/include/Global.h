#ifndef GLOBAL_H
#define GLOBAL_H

#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <dirent.h>

using namespace std;

//常量
const int SERVPORT = 3333;  //端口号
const int BACKLOG = 10;     //最大同时连接请求数
const int CACHESIZE = 1024; //缓冲区大小
const int N = 64;           //命令行参数
#endif