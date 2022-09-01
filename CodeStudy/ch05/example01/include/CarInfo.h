#ifndef CAR_INFO_H
#define CAR_INFO_H

#include "./Global.h"

/**
 * @brief 车辆信息结构体
 *
 */
typedef struct
{
    long int serialNum; //车辆序列码
    std::string brand;  //品牌
} CarInfo;

#endif