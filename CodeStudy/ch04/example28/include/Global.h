#ifndef GLOBAL_H
#define GLOBAL_H

#include <iostream>
#include <string>
#include <memory>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <climits>

using namespace std;

//输出自定义错误信息
#define handle_error_en(en, msg) \
    do                           \
    {                            \
        errno = en;              \
        perror(msg);             \
        exit(EXIT_FAILURE);      \
    } while (0)

//常量
const int CACHE_SIZE = 10;      //缓冲区大小
const int THREAD_PRODUCER = 10; //生产者线程数量
const int THREAD_CONSUMER = 10; //消费者线程数量

#endif