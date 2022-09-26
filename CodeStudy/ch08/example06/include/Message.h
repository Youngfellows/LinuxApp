#ifndef MESSAGE_H
#define MESSAGE_H

#include "./Constant.h"

/**
 * @brief 消息结构体
 *
 */
typedef struct Message
{
    int msgType;               //消息类型
    char msgText[BUFFER_SIZE]; //消息内容
} Message, *PMessage;

#endif