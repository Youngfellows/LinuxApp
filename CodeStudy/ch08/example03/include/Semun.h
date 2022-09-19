#ifndef SEMUN_H
#define SEMUN_H

#include "./Global.h"

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *_buf;
};

#endif