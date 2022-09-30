#ifndef TFT_H
#define TFT_H

#define USE_HORIZONTAL 0  //设置横屏或者竖屏显示 0或1为竖屏 2或3为横屏

#if USE_HORIZONTAL == 0 || USE_HORIZONTAL == 1
    #define WIDTH 240
    #define HEIGHT 320
#else
    #define WIDTH 320
    #define HEIGHT 240
#endif

#define PI 3.141592

#include "spi.h"
#include "bsp.h"
#include "gpio.h"
#include "math.h"
#include "string.h"

uint16_t RGB2565(uint8_t red, uint8_t green, uint8_t blue);

void TFT_Init(void);
void TFT_Fill(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void TFT_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void TFT_DrawArc(uint16_t centerx, uint16_t centery, uint16_t radius, int16_t deg1, int16_t deg2, uint16_t color);
void TFT_DrawStr(uint16_t x, uint16_t y, char* str, uint16_t color);
char* TFT_Itoa(short num);
void TFT_Test(void);
#endif