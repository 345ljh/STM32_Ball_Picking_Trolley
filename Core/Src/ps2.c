#include "ps2.h"

void PS2_ReadData(uint8_t* rx)
{
    uint8_t cmd_start = 0x01;
    uint8_t cmd_ask = 0x42;
    uint8_t cmd_null = 0x00;
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
    HAL_SPI_TransmitReceive(&hspi1, &cmd_start, &rx[0], 1, 100);
    delay_us(10);
    HAL_SPI_TransmitReceive(&hspi1, &cmd_ask, &rx[1], 1, 100);
    delay_us(10);
    for(int i = 2; i <= 8; i++)
    {
        HAL_SPI_TransmitReceive(&hspi1, &cmd_null, &rx[i], 1, 100);
        delay_us(10);
    }
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
}

void PS2_Solve(robot_state* obj, uint8_t* rx)
{
    obj->music = !(rx[4] & 0x10);
    if(rx[1] == 0x73)
    {
        obj->control = REMOTE;

        if( !(rx[4] & 0x04) && (rx[4] & 0x01) ) obj->frame = UP;
        else if( (rx[4] & 0x04) && !(rx[4] & 0x01) ) obj->frame = DOWN;

        obj->vx = rx[5] - 128;
        obj->vy = 127 - rx[6];
        obj->rorate = rx[7] - 128;
    }
    else if(rx[1] == 0x41)
    {
        obj->control = AUTO;
        obj->frame = UP;

        if(obj->bally > 100)  //距离过近
        {
            obj->vx = 0;
            obj->vy = -50;
            obj->rorate = 0;
        }
        else if(obj->ballpix >= 1600)  //在框范围内
        {
            obj->vx = 0;
            obj->vy = 0;
            obj->rorate = 0;

            obj->frame = DOWN;
            HAL_Delay(1500);
            obj->frame = UP;
            HAL_Delay(1500);
        }
        else if(obj->ballpix == 0)  //未检测到
        {
            obj->vx = 0;
            obj->vy = 0;
            obj->rorate = obj->connect == SUCCEED ? (obj->direct == LEFT ? -80 : 80) : 0;
        }
        else
        {
            obj->vx = (obj->ballx - 120) / 2;
            if(obj->ballx > 120) obj->direct = RIGHT;
            else obj->direct = LEFT;
            obj->vy = 127;
            obj->rorate = 0;
        }
    }
    else
    {
        obj->control = ERR;
        //obj->frame = UP;
        obj->vx = 0;
        obj->vy = 0;
        obj->rorate = 0;
    }
}