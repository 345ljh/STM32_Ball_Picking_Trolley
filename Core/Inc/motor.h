#ifndef MOTOR_H
#define MOTOR_H

#include "tim.h"
#include "stm32f1xx_hal.h"
#include "math.h"
#include "ps2.h"

#define OUTPUTMAX 192.0

//电机结构体,所有电机均使用TIM3
typedef struct motor_t
{
    __IO uint32_t* ccr;  //TIM通道,传入TIM3->CCRx
    GPIO_TypeDef* gpio;  //GPIOA~D
    uint16_t in1;  //输入引脚1
    uint16_t in2;  //输入引脚2
}motor;
//IN1=0,IN2=1正转  IN1=1,IN2=0反转

void Motor_Init(motor* obj, __IO uint32_t* ccr, GPIO_TypeDef* gpio, uint16_t in1, uint16_t in2);
void Motor_Control(motor* lf, motor* rf, motor* rb, motor* lb, robot_state* state);
void Motor_Update(motor* obj, int speed);

#endif
