#ifndef GLOBAL_H
#define GLOBAL_H

#include <iostream>
#include <string>
#include <memory>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <fcntl.h>
#include <utime.h>
#include <string.h>
#include <dirent.h>
#include <linux/fs.h>

using namespace std;

const int FLAG_FILE = 1; //文件类型
const int FLAG_DIR = 0;  //目录类型

#endif