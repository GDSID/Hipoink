#ifndef _DISPLAY_EPD_W21_H_
#define _DISPLAY_EPD_W21_H_

#define EPD_W21_WRITE_DATA 1
#define EPD_W21_WRITE_CMD  0
#include "sys.h"
extern void driver_delay_us(unsigned int xus);
extern void driver_delay_xms(unsigned long xms);
extern void EPD_Reset(void);	
#define KEY0  PEin(11)//GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_11)//¶ÁÈ¡°´¼ü0


#endif
/***********************************************************
						end file
***********************************************************/


