#include "bsp.h"

void delay_us(int nus)
{
    uint16_t differ = 0xffff - nus - 5;

    __HAL_TIM_SetCounter(&htim5, differ);
    //开启定时器
    HAL_TIM_Base_Start(&htim5);
 
    while( differ<0xffff-5)
    {
    differ = __HAL_TIM_GetCounter(&htim5);
    };
    //关闭定时器
    HAL_TIM_Base_Stop(&htim5);
}