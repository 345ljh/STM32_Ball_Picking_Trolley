#include "motor.h"

//设置连接TB2216输入的引脚
void Motor_Init(motor* obj, __IO uint32_t* ccr, GPIO_TypeDef* gpio, uint16_t in1, uint16_t in2)
{
    obj->ccr = ccr;
    obj->gpio = gpio;
    obj->in1 = in1;
    obj->in2 = in2;

    HAL_GPIO_WritePin(obj->gpio, obj->in2, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(obj->gpio, obj->in1, GPIO_PIN_RESET);
}

void Motor_Control(motor* lf, motor* rf, motor* rb, motor* lb, robot_state* state)
{
    
    int speed[4] = {0}; //分别表示lf, rf, rb, lb
    speed[0] = -state->vx - state->vy - state->rorate;
    speed[1] = state->vx - state->vy + state->rorate;
    speed[2] = -state->vx - state->vy + state->rorate;
    speed[3] = state->vx - state->vy - state->rorate;

    for(int i = 0; i <= 3; i++)
    {
        if(speed[i] > OUTPUTMAX) speed[i] = OUTPUTMAX;
        else if(speed[i] < -OUTPUTMAX) speed[i] = -OUTPUTMAX;
    }

    Motor_Update(lf, speed[0]);
    Motor_Update(rf, speed[1]);
    Motor_Update(rb, speed[2]);
    Motor_Update(lb, speed[3]);
}

void Motor_Update(motor* obj, int speed)
{
    if(speed > 0)
    {
        HAL_GPIO_WritePin(obj->gpio, obj->in2, GPIO_PIN_SET);
        HAL_GPIO_WritePin(obj->gpio, obj->in1, GPIO_PIN_RESET);
    }
    else
    {
        HAL_GPIO_WritePin(obj->gpio, obj->in1, GPIO_PIN_SET);
        HAL_GPIO_WritePin(obj->gpio, obj->in2, GPIO_PIN_RESET);
    }
    *(obj->ccr) = TIM2->ARR * (fabs(speed) / OUTPUTMAX);
}