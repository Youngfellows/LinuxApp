#ifndef CAR_INFO_H
#define CAR_INFO_H

#include "./Global.h"

/**
 * @brief 车辆信息结构体
 *
 */
typedef struct
{
    std::string brand;     //品牌
    long int serialNumber; //序列号
} CarInfo;

#endif