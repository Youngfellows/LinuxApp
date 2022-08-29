#ifndef GLOBAL_H
#define GLOBAL_H

#include <iostream>
#include <string>
#include <memory>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sched.h>
#include <pthread.h>
#include <assert.h>
#include <unistd.h>

using namespace std;

//输出自定义错误信息
#define handle_error_en(en, msg) \
    do                           \
    {                            \
        errno = en;              \
        perror(msg);             \
        exit(EXIT_FAILURE);      \
    } while (0)

#endif