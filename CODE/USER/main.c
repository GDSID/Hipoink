#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"
//EPD
#include "Display_EPD_W21_spi.h"
#include "Display_EPD_W21.h"
//#include "Ap_29demo.h"	
//GUI
#include "GUI_Paint.h"
#include "fonts.h"


extern const unsigned char gImage_1[10800];

unsigned char HRES,VRES_byte1,VRES_byte2;

int	main(void)
{
		delay_init();	    	     //Delay function initialization
		NVIC_Configuration(); 	//Set NVIC interrupt grouping 2
    EPD_GPIO_Init();       //EPD GPIO  initialization
	
	while(1)
	{

		
			EPD_init();
		PIC_display(PIC_BLACK);
		delay_s(1);	
		
		EPD_init();
		PIC_display(PIC_WHITE);
		delay_s(1);	

		
				EPD_W21_Init();             //Electronic paper IC reset							
		LED4_0;
		EPD_init();
		PIC_Image(gImage_1);
		LED4_1;
//		EPD_sleep();//EPD_sleep,Sleep instruction is necessary, please do not delete!!!
	  delay_s(1);	
		while(1);
	}
}	


