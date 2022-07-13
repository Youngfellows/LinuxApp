#ifndef GLOBAL_H
#define GLOBAL_H

#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <thread>
#include <mutex>
#include <vector>
#include <algorithm>
#include <functional>
#include <condition_variable>
#include <chrono>

#include <unistd.h>      // for syscall()
#include <sys/syscall.h> // for SYS_xxx definitions

using namespace std;

//定义常数
const int SERVER_PORT = 3333;   //服务器短监听端口号
const int BACKLOG = 10;         //最大同时连接请求数
const int MAX_DATA_SIZE = 1024; //接收、发送数据缓冲区

#endif