#ifndef AUDIO_H
#define AUDIO_H

#include "./Global.h"

/**
 * @brief 音频数据结构体
 *
 */
typedef struct
{
    int id;          //序列号
    std::string pcm; //音频数据
} Audio;

#endif