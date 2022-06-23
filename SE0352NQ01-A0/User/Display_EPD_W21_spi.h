#ifndef _MCU_SPI_H_
#define _MCU_SPI_H_
#include "stm32f10x.h"

#define EPD_W21_SPI_SPEED 0x02

#define EPD_W21_MOSI_0	GPIO_ResetBits(GPIOD, GPIO_Pin_10)
#define EPD_W21_MOSI_1	GPIO_SetBits(GPIOD, GPIO_Pin_10)

#define EPD_W21_CLK_0	GPIO_ResetBits(GPIOD, GPIO_Pin_9)
#define EPD_W21_CLK_1	GPIO_SetBits(GPIOD, GPIO_Pin_9)

#define EPD_W21_CS_0	GPIO_ResetBits(GPIOD, GPIO_Pin_8)
#define EPD_W21_CS_1	GPIO_SetBits(GPIOD, GPIO_Pin_8)

#define EPD_W21_DC_0	GPIO_ResetBits(GPIOE, GPIO_Pin_15)
#define EPD_W21_DC_1	GPIO_SetBits(GPIOE, GPIO_Pin_15)

#define EPD_W21_RST_0	GPIO_ResetBits(GPIOE, GPIO_Pin_14)
#define EPD_W21_RST_1	GPIO_SetBits(GPIOE, GPIO_Pin_14)

#define isEPD_W21_BUSY GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_13) // for solomen solutions

extern void driver_delay_us(unsigned int xus);
extern void driver_delay_xms(unsigned long xms);

void SPI_Write(unsigned char value);
void EPD_W21_WriteDATA(unsigned char command);
void EPD_W21_WriteCMD(unsigned char command);


#endif  //#ifndef _MCU_SPI_H_

/***********************************************************
						end file
***********************************************************/
