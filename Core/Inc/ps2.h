#ifndef PS2_H
#define PS2_H

#include "tim.h"
#include "spi.h"
#include "gpio.h"
#include "bsp.h"
#include "stm32f1xx_hal.h"

#include "string.h"

typedef enum {REMOTE, AUTO, ERR} control_state;
typedef enum {DOWN, UP} frame_state;
typedef enum {INIT, SUCCEED, FAILED} connect_state;
typedef enum {LEFT, RIGHT} find_direct;

typedef struct robot_state_t
{
    control_state control;  //控制方式
    frame_state frame;  //球框状态
    connect_state connect;  //通信状态
    find_direct direct;  //寻找时旋转方向

    int8_t vx;
    int8_t vy;
    int8_t rorate;

    //openmv回传数据
    uint8_t ballx;
    uint8_t bally;
    uint16_t ballpix;

    uint8_t music;
}robot_state;

void PS2_ReadData(uint8_t* rx);
void PS2_Solve(robot_state* obj, uint8_t* rx);

#endif