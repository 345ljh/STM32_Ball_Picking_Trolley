#include "tft.h"

//字符点阵,大小为8*16
uint8_t TFT_chara[][16] = {
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*" ",0*/
{0x00,0x00,0x00,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x00,0x00,0x18,0x18,0x00,0x00},/*"!",1*/
{0x00,0x48,0x6C,0x24,0x12,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*""",2*/
{0x00,0x00,0x00,0x24,0x24,0x24,0x7F,0x12,0x12,0x12,0x7F,0x12,0x12,0x12,0x00,0x00},/*"#",3*/
{0x00,0x00,0x08,0x1C,0x2A,0x2A,0x0A,0x0C,0x18,0x28,0x28,0x2A,0x2A,0x1C,0x08,0x08},/*"$",4*/
{0x00,0x00,0x00,0x22,0x25,0x15,0x15,0x15,0x2A,0x58,0x54,0x54,0x54,0x22,0x00,0x00},/*"%",5*/
{0x00,0x00,0x00,0x0C,0x12,0x12,0x12,0x0A,0x76,0x25,0x29,0x11,0x91,0x6E,0x00,0x00},/*"&",6*/
{0x00,0x06,0x06,0x04,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"'",7*/
{0x00,0x40,0x20,0x10,0x10,0x08,0x08,0x08,0x08,0x08,0x08,0x10,0x10,0x20,0x40,0x00},/*"(",8*/
{0x00,0x02,0x04,0x08,0x08,0x10,0x10,0x10,0x10,0x10,0x10,0x08,0x08,0x04,0x02,0x00},/*")",9*/
{0x00,0x00,0x00,0x00,0x08,0x08,0x6B,0x1C,0x1C,0x6B,0x08,0x08,0x00,0x00,0x00,0x00},/*"*",10*/
{0x00,0x00,0x00,0x00,0x08,0x08,0x08,0x08,0x7F,0x08,0x08,0x08,0x08,0x00,0x00,0x00},/*"+",11*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x06,0x04,0x03},/*",",12*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"-",13*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x06,0x00,0x00},/*".",14*/
{0x00,0x00,0x80,0x40,0x40,0x20,0x20,0x10,0x10,0x08,0x08,0x04,0x04,0x02,0x02,0x00},/*"/",15*/
{0x00,0x00,0x00,0x18,0x24,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x24,0x18,0x00,0x00},/*"0",16*/
{0x00,0x00,0x00,0x08,0x0E,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x3E,0x00,0x00},/*"1",17*/
{0x00,0x00,0x00,0x3C,0x42,0x42,0x42,0x20,0x20,0x10,0x08,0x04,0x42,0x7E,0x00,0x00},/*"2",18*/
{0x00,0x00,0x00,0x3C,0x42,0x42,0x20,0x18,0x20,0x40,0x40,0x42,0x22,0x1C,0x00,0x00},/*"3",19*/
{0x00,0x00,0x00,0x20,0x30,0x28,0x24,0x24,0x22,0x22,0x7E,0x20,0x20,0x78,0x00,0x00},/*"4",20*/
{0x00,0x00,0x00,0x7E,0x02,0x02,0x02,0x1A,0x26,0x40,0x40,0x42,0x22,0x1C,0x00,0x00},/*"5",21*/
{0x00,0x00,0x00,0x38,0x24,0x02,0x02,0x1A,0x26,0x42,0x42,0x42,0x24,0x18,0x00,0x00},/*"6",22*/
{0x00,0x00,0x00,0x7E,0x22,0x22,0x10,0x10,0x08,0x08,0x08,0x08,0x08,0x08,0x00,0x00},/*"7",23*/
{0x00,0x00,0x00,0x3C,0x42,0x42,0x42,0x24,0x18,0x24,0x42,0x42,0x42,0x3C,0x00,0x00},/*"8",24*/
{0x00,0x00,0x00,0x18,0x24,0x42,0x42,0x42,0x64,0x58,0x40,0x40,0x24,0x1C,0x00,0x00},/*"9",25*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00},/*":",26*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x08,0x08,0x04},/*";",27*/
{0x00,0x00,0x00,0x40,0x20,0x10,0x08,0x04,0x02,0x04,0x08,0x10,0x20,0x40,0x00,0x00},/*"<",28*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0x00,0x00,0x00,0x7F,0x00,0x00,0x00,0x00,0x00},/*"=",29*/
{0x00,0x00,0x00,0x02,0x04,0x08,0x10,0x20,0x40,0x20,0x10,0x08,0x04,0x02,0x00,0x00},/*">",30*/
{0x00,0x00,0x00,0x3C,0x42,0x42,0x46,0x40,0x20,0x10,0x10,0x00,0x18,0x18,0x00,0x00},/*"?",31*/
{0x00,0x00,0x00,0x1C,0x22,0x5A,0x55,0x55,0x55,0x55,0x2D,0x42,0x22,0x1C,0x00,0x00},/*"@",32*/
{0x00,0x00,0x00,0x08,0x08,0x18,0x14,0x14,0x24,0x3C,0x22,0x42,0x42,0xE7,0x00,0x00},/*"A",33*/
{0x00,0x00,0x00,0x1F,0x22,0x22,0x22,0x1E,0x22,0x42,0x42,0x42,0x22,0x1F,0x00,0x00},/*"B",34*/
{0x00,0x00,0x00,0x7C,0x42,0x42,0x01,0x01,0x01,0x01,0x01,0x42,0x22,0x1C,0x00,0x00},/*"C",35*/
{0x00,0x00,0x00,0x1F,0x22,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x22,0x1F,0x00,0x00},/*"D",36*/
{0x00,0x00,0x00,0x3F,0x42,0x12,0x12,0x1E,0x12,0x12,0x02,0x42,0x42,0x3F,0x00,0x00},/*"E",37*/
{0x00,0x00,0x00,0x3F,0x42,0x12,0x12,0x1E,0x12,0x12,0x02,0x02,0x02,0x07,0x00,0x00},/*"F",38*/
{0x00,0x00,0x00,0x3C,0x22,0x22,0x01,0x01,0x01,0x71,0x21,0x22,0x22,0x1C,0x00,0x00},/*"G",39*/
{0x00,0x00,0x00,0xE7,0x42,0x42,0x42,0x42,0x7E,0x42,0x42,0x42,0x42,0xE7,0x00,0x00},/*"H",40*/
{0x00,0x00,0x00,0x3E,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x3E,0x00,0x00},/*"I",41*/
{0x00,0x00,0x00,0x7C,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x11,0x0F},/*"J",42*/
{0x00,0x00,0x00,0x77,0x22,0x12,0x0A,0x0E,0x0A,0x12,0x12,0x22,0x22,0x77,0x00,0x00},/*"K",43*/
{0x00,0x00,0x00,0x07,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x42,0x7F,0x00,0x00},/*"L",44*/
{0x00,0x00,0x00,0x77,0x36,0x36,0x36,0x36,0x2A,0x2A,0x2A,0x2A,0x2A,0x6B,0x00,0x00},/*"M",45*/
{0x00,0x00,0x00,0xE3,0x46,0x46,0x4A,0x4A,0x52,0x52,0x52,0x62,0x62,0x47,0x00,0x00},/*"N",46*/
{0x00,0x00,0x00,0x1C,0x22,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x22,0x1C,0x00,0x00},/*"O",47*/
{0x00,0x00,0x00,0x3F,0x42,0x42,0x42,0x42,0x3E,0x02,0x02,0x02,0x02,0x07,0x00,0x00},/*"P",48*/
{0x00,0x00,0x00,0x1C,0x22,0x41,0x41,0x41,0x41,0x41,0x4D,0x53,0x32,0x1C,0x60,0x00},/*"Q",49*/
{0x00,0x00,0x00,0x3F,0x42,0x42,0x42,0x3E,0x12,0x12,0x22,0x22,0x42,0xC7,0x00,0x00},/*"R",50*/
{0x00,0x00,0x00,0x7C,0x42,0x42,0x02,0x04,0x18,0x20,0x40,0x42,0x42,0x3E,0x00,0x00},/*"S",51*/
{0x00,0x00,0x00,0x7F,0x49,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x1C,0x00,0x00},/*"T",52*/
{0x00,0x00,0x00,0xE7,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x3C,0x00,0x00},/*"U",53*/
{0x00,0x00,0x00,0xE7,0x42,0x42,0x22,0x24,0x24,0x14,0x14,0x18,0x08,0x08,0x00,0x00},/*"V",54*/
{0x00,0x00,0x00,0x6B,0x49,0x49,0x49,0x49,0x55,0x55,0x36,0x22,0x22,0x22,0x00,0x00},/*"W",55*/
{0x00,0x00,0x00,0xE7,0x42,0x24,0x24,0x18,0x18,0x18,0x24,0x24,0x42,0xE7,0x00,0x00},/*"X",56*/
{0x00,0x00,0x00,0x77,0x22,0x22,0x14,0x14,0x08,0x08,0x08,0x08,0x08,0x1C,0x00,0x00},/*"Y",57*/
{0x00,0x00,0x00,0x7E,0x21,0x20,0x10,0x10,0x08,0x04,0x04,0x42,0x42,0x3F,0x00,0x00},/*"Z",58*/
{0x00,0x78,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x78,0x00},/*"[",59*/
{0x00,0x00,0x02,0x02,0x04,0x04,0x08,0x08,0x08,0x10,0x10,0x20,0x20,0x20,0x40,0x40},/*"\",60*/
{0x00,0x1E,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x1E,0x00},/*"]",61*/
{0x00,0x38,0x44,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"^",62*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF},/*"_",63*/
{0x00,0x06,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"`",64*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x42,0x78,0x44,0x42,0x42,0xFC,0x00,0x00},/*"a",65*/
{0x00,0x00,0x00,0x03,0x02,0x02,0x02,0x1A,0x26,0x42,0x42,0x42,0x26,0x1A,0x00,0x00},/*"b",66*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x44,0x02,0x02,0x02,0x44,0x38,0x00,0x00},/*"c",67*/
{0x00,0x00,0x00,0x60,0x40,0x40,0x40,0x78,0x44,0x42,0x42,0x42,0x64,0xD8,0x00,0x00},/*"d",68*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x42,0x7E,0x02,0x02,0x42,0x3C,0x00,0x00},/*"e",69*/
{0x00,0x00,0x00,0xF0,0x88,0x08,0x08,0x7E,0x08,0x08,0x08,0x08,0x08,0x3E,0x00,0x00},/*"f",70*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7C,0x22,0x22,0x1C,0x02,0x3C,0x42,0x42,0x3C},/*"g",71*/
{0x00,0x00,0x00,0x03,0x02,0x02,0x02,0x3A,0x46,0x42,0x42,0x42,0x42,0xE7,0x00,0x00},/*"h",72*/
{0x00,0x00,0x00,0x0C,0x0C,0x00,0x00,0x0E,0x08,0x08,0x08,0x08,0x08,0x3E,0x00,0x00},/*"i",73*/
{0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x38,0x20,0x20,0x20,0x20,0x20,0x20,0x22,0x1E},/*"j",74*/
{0x00,0x00,0x00,0x03,0x02,0x02,0x02,0x72,0x12,0x0A,0x16,0x12,0x22,0x77,0x00,0x00},/*"k",75*/
{0x00,0x00,0x00,0x0E,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x3E,0x00,0x00},/*"l",76*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0x92,0x92,0x92,0x92,0x92,0xB7,0x00,0x00},/*"m",77*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3B,0x46,0x42,0x42,0x42,0x42,0xE7,0x00,0x00},/*"n",78*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x42,0x42,0x42,0x42,0x42,0x3C,0x00,0x00},/*"o",79*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1B,0x26,0x42,0x42,0x42,0x22,0x1E,0x02,0x07},/*"p",80*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x78,0x44,0x42,0x42,0x42,0x44,0x78,0x40,0xE0},/*"q",81*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x77,0x4C,0x04,0x04,0x04,0x04,0x1F,0x00,0x00},/*"r",82*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7C,0x42,0x02,0x3C,0x40,0x42,0x3E,0x00,0x00},/*"s",83*/
{0x00,0x00,0x00,0x00,0x00,0x08,0x08,0x3E,0x08,0x08,0x08,0x08,0x08,0x30,0x00,0x00},/*"t",84*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x63,0x42,0x42,0x42,0x42,0x62,0xDC,0x00,0x00},/*"u",85*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE7,0x42,0x24,0x24,0x14,0x08,0x08,0x00,0x00},/*"v",86*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xEB,0x49,0x49,0x55,0x55,0x22,0x22,0x00,0x00},/*"w",87*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x76,0x24,0x18,0x18,0x18,0x24,0x6E,0x00,0x00},/*"x",88*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE7,0x42,0x24,0x24,0x14,0x18,0x08,0x08,0x07},/*"y",89*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7E,0x22,0x10,0x08,0x08,0x44,0x7E,0x00,0x00},/*"z",90*/
{0x00,0xC0,0x20,0x20,0x20,0x20,0x20,0x10,0x20,0x20,0x20,0x20,0x20,0x20,0xC0,0x00},/*"{",91*/
{0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10},/*"|",92*/
{0x00,0x06,0x08,0x08,0x08,0x08,0x08,0x10,0x08,0x08,0x08,0x08,0x08,0x08,0x06,0x00},/*"}",93*/
{0x0C,0x32,0xC2,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"~",94*/
};

//发送1字节数据
void TFT_WriteData(uint8_t data)
{
    HAL_GPIO_WritePin(TFT_DC_GPIO_Port, TFT_DC_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(TFT_CS_GPIO_Port, TFT_CS_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi2, &data, 1, 100);
    HAL_GPIO_WritePin(TFT_CS_GPIO_Port, TFT_CS_Pin, GPIO_PIN_SET);
}

//发送2字节数据
void TFT_WriteData16(uint16_t data)
{
    uint8_t high = data >> 8;
    uint8_t low = data & 0xFF;
    HAL_GPIO_WritePin(TFT_DC_GPIO_Port, TFT_DC_Pin, GPIO_PIN_SET);

    HAL_GPIO_WritePin(TFT_CS_GPIO_Port, TFT_CS_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi2, &high, 1, 100);
    HAL_GPIO_WritePin(TFT_CS_GPIO_Port, TFT_CS_Pin, GPIO_PIN_SET);

    HAL_GPIO_WritePin(TFT_CS_GPIO_Port, TFT_CS_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi2, &low, 1, 100);
    HAL_GPIO_WritePin(TFT_CS_GPIO_Port, TFT_CS_Pin, GPIO_PIN_SET);
}

//发送命令
void TFT_WriteCMD(uint8_t cmd)
{
    HAL_GPIO_WritePin(TFT_DC_GPIO_Port, TFT_DC_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(TFT_CS_GPIO_Port, TFT_CS_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi2, &cmd, 1, 100);
    HAL_GPIO_WritePin(TFT_CS_GPIO_Port, TFT_CS_Pin, GPIO_PIN_SET);
}

void TFT_Init()
{
    HAL_GPIO_WritePin(TFT_BL_GPIO_Port, TFT_BL_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(TFT_RESET_GPIO_Port, TFT_RESET_Pin, GPIO_PIN_RESET);
    HAL_Delay(50);
    HAL_GPIO_WritePin(TFT_RESET_GPIO_Port, TFT_RESET_Pin, GPIO_PIN_SET);
    HAL_Delay(50);
    HAL_GPIO_WritePin(TFT_BL_GPIO_Port, TFT_BL_Pin, GPIO_PIN_SET);

	TFT_WriteCMD(0x11); 
	HAL_Delay(10); 
	
	//display and color format setting
	TFT_WriteCMD(0x36);

	if(USE_HORIZONTAL == 0)TFT_WriteData(0x00);
	else if(USE_HORIZONTAL == 1)TFT_WriteData(0xC0);
	else if(USE_HORIZONTAL == 2)TFT_WriteData(0x70);
	else TFT_WriteData(0xA0);

	TFT_WriteCMD(0x3A);
	TFT_WriteData(0x05);

	//frame rate setting
	TFT_WriteCMD(0xB2);
	TFT_WriteData(0x0C);
	TFT_WriteData(0x0C);
	TFT_WriteData(0x00);
	TFT_WriteData(0x33);
	TFT_WriteData(0x33); 

	TFT_WriteCMD(0xB7); 
	TFT_WriteData(0x35);  

	//power setting
	TFT_WriteCMD(0xBB);
	TFT_WriteData(0x35);

	TFT_WriteCMD(0xC0);
	TFT_WriteData(0x2C);

	TFT_WriteCMD(0xC2);
	TFT_WriteData(0x01);

	TFT_WriteCMD(0xC3);
	TFT_WriteData(0x13);   

	TFT_WriteCMD(0xC4);
	TFT_WriteData(0x20);  

	TFT_WriteCMD(0xC6); 
	TFT_WriteData(0x0F);    

	TFT_WriteCMD(0xCA); 
	TFT_WriteData(0x0F);  

	TFT_WriteCMD(0xC8); 
	TFT_WriteData(0x08);  

	TFT_WriteCMD(0x55); 
	TFT_WriteData(0x90);  

	TFT_WriteCMD(0xD0); 
	TFT_WriteData(0xA4);  
	TFT_WriteData(0xA1);  

	//gamma setting
	TFT_WriteCMD(0xE0);
	TFT_WriteData(0xD0);
	TFT_WriteData(0x00);
	TFT_WriteData(0x06);
	TFT_WriteData(0x09);
	TFT_WriteData(0x0B);
	TFT_WriteData(0x2A);
	TFT_WriteData(0x3C);
	TFT_WriteData(0x55);
	TFT_WriteData(0x4B);
	TFT_WriteData(0x08);
	TFT_WriteData(0x16);
	TFT_WriteData(0x14);
	TFT_WriteData(0x19);
	TFT_WriteData(0x20);

	TFT_WriteCMD(0xE1);
	TFT_WriteData(0xD0);
	TFT_WriteData(0x00);
	TFT_WriteData(0x06);
	TFT_WriteData(0x09);
	TFT_WriteData(0x0B);
	TFT_WriteData(0x29);
	TFT_WriteData(0x36);
	TFT_WriteData(0x54);
	TFT_WriteData(0x4B);
	TFT_WriteData(0x0D);
	TFT_WriteData(0x16);
	TFT_WriteData(0x14);
	TFT_WriteData(0x21);
	TFT_WriteData(0x20);

	TFT_WriteCMD(0x29);

}

void TFT_SetPos(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	//x1写0无法更新,需要写1
    #if (USE_HORIZONTAL == 0 || USE_HORIZONTAL == 1)
        TFT_WriteCMD(0x2A);
        TFT_WriteData16(x1);
        TFT_WriteData16(x2);
        TFT_WriteCMD(0x2B);
        TFT_WriteData16(y1);
        TFT_WriteData16(y2);
        TFT_WriteCMD(0x2C);
    #else
        TFT_WriteCMD(0x2A);
        TFT_WriteData16(x1);
        TFT_WriteData16(x2);
        TFT_WriteCMD(0x2B);
        TFT_WriteData16(y1 + 34);
        TFT_WriteData16(y2 + 34);
        TFT_WriteCMD(0x2C);
    #endif

}

//RGB转565颜色
uint16_t RGB2565(uint8_t red, uint8_t green, uint8_t blue)
{
	return ( (red >> 3 << 11) + (green >> 2 << 5) + (blue >> 3));
}

//填充
void TFT_Fill(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
	TFT_SetPos(x1, y1 - 1, x2, y2 - 1);
	for(uint16_t i = x1; i <= x2 - 1; i++)
	{
		for(uint16_t j = y1; j <= y2 - 1; j++)
			TFT_WriteData16(color);
	}
}

//画线
void TFT_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
	//竖直线
	if(x1 == x2)
	{
		if(y1 <= y2)
		{
			for(uint16_t y = y1; y <= y2 - 1; y++)
			{
				TFT_SetPos(x1, y, x1, y);
				TFT_WriteData16(color);
			}
		}
		else
		{
			for(uint16_t y = y2; y <= y1 - 1; y++)
			{
				TFT_SetPos(x1, y, x1, y);
				TFT_WriteData16(color);
			}
		}
	}
	else
	{
		float k = (y2 - y1) * 1.0 / (x2 - x1);
		float b = y1 - k * x1;
		if(x1 <= x2)
		{
			for(uint16_t x = x1; x <= x2 - 1; x++)
			{
				uint16_t y = (uint16_t)(k * x + b);
				TFT_SetPos(x, y, x, y);
				TFT_WriteData16(color);
			}
		}
		else
		{
			for(uint16_t x = x2; x <= x1 - 1; x++)
			{
				uint16_t y = (uint16_t)(k * x + b);
				TFT_SetPos(x, y, x, y);
				TFT_WriteData16(color);
			}
		}
	}
}

//画圆弧
void TFT_DrawArc(uint16_t centerx, uint16_t centery, uint16_t radius, int16_t deg1, int16_t deg2, uint16_t color)
{
	if(deg1 <= deg2)
	{
		for(int16_t deg = deg1; deg <= deg2; deg++)
		{
			uint16_t x = centerx + radius * cos(deg * PI / 180);
			uint16_t y = centery - radius * sin(deg * PI / 180);
			if(x >= 1 && x <= WIDTH && y >= 0 && y <= HEIGHT)
			{
				TFT_SetPos(x, y, x, y);
				TFT_WriteData16(color);
			}
		}
	}
	else
	{
		for(int16_t deg = deg2; deg <= deg1; deg++)
		{
			uint16_t x = centerx + radius * cos(deg * PI / 180);
			uint16_t y = centery - radius * sin(deg * PI / 180);
			if(x >= 1 && x <= WIDTH && y >= 0 && y <= HEIGHT)
			{
				TFT_SetPos(x, y, x, y);
				TFT_WriteData16(color);
			}
		}
	}
}

//写字
void TFT_DrawStr(uint16_t x, uint16_t y, char* str, uint16_t color)
{
	uint8_t len = strlen(str);
	for(int i = 0; i <= len - 1; i++)
	{
		TFT_SetPos(x + 8 * i, y, x + 8 * i + 7, y + 15);
		for(int j = 0; j <= 15; j++)
			for(int k = 0; k <= 7; k++) TFT_WriteData16(TFT_chara[str[i] - ' '][j] & (1 << k) ? color : 0);
	}
}

//数字转字符串(字符串有效长度不超过6位)
char* TFT_Itoa(int16_t num)
{
	static char str[7] = "";
	memset(str, 0, 7 * sizeof(char));

	if(num == 0)
    {
        strcat(str, "0     ");
        return str;
    }
	else if(num < 0)
	{
		strcat(str, "-");
		num = -num;
	}

	int digit = (int)(log10(num));
	printf("%d\n", digit);
	for(int i = digit; i >= 0; i--)
	{
		char temp[2] = "";
		temp[0] = num / pow(10, i) + '0';
		strcat(str, temp);
		num %= (int)pow(10, i);
	}

	//补空格
	for(int i = 0; i <= 5; i++)
	{
		if(!str[i]) str[i] = ' ';
	}
	return str;
}

//初始测试程序
void TFT_Test(void)
{  
  TFT_DrawArc(120, 160, 60, 0, 360, RGB2565(200, 184, 248));

  TFT_DrawArc(60, 202, 74, 40, 83, RGB2565(255, 201, 14));
  TFT_DrawArc(113, 158, 5, -116, 39, RGB2565(255, 201, 14));
  TFT_DrawLine(97, 150, 110, 163, RGB2565(255, 201, 14));
  TFT_DrawArc(108, 166, 4, -133, 47, RGB2565(255, 201, 14));
  TFT_DrawLine(93, 157, 105, 168, RGB2565(255, 201, 14));
  TFT_DrawArc(105, 169, 5, -85, 8, RGB2565(255, 201, 14));
  TFT_DrawLine(97, 150, 110, 163, RGB2565(255, 201, 14));
  TFT_DrawArc(75, 189, 28, 44, 90, RGB2565(255, 201, 14));
  TFT_DrawArc(76, 166, 5, 120, 252, RGB2565(255, 201, 14));
  TFT_DrawLine(73, 170, 95, 181, RGB2565(255, 201, 14));
  TFT_DrawArc(92, 186, 5, -92, 60, RGB2565(255, 201, 14));
  TFT_DrawArc(93, 156, 34, -82, -162, RGB2565(255, 201, 14));

  TFT_DrawArc(111, 181, 32, -112, -166, RGB2565(173, 221, 247));
  TFT_DrawArc(119, 167, 47, 36, -114, RGB2565(173, 221, 247));
  TFT_DrawArc(132, 161, 33, 42, 147, RGB2565(173, 221, 247));
  TFT_DrawArc(123, 185, 40, 110, 80, RGB2565(173, 221, 247));
  TFT_DrawArc(126, 167, 22, 79, -156, RGB2565(173, 221, 247));
  TFT_DrawArc(95, 184, 15, 38, 140, RGB2565(173, 221, 247));

  TFT_DrawArc(93, 176, 2, 0, 360, RGB2565(252, 67, 14));

  HAL_Delay(200);
  TFT_Fill(60, 100, 180, 230, 0);
}