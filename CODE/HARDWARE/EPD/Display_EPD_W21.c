#include "Display_EPD_W21_spi.h"
#include "Display_EPD_W21.h"
#include "Ap_29demo.h"	
#include "core_cm3.h"

#define Source_Pixel  240    //  
#define Gate_Pixel    360    //


void delay_xms(unsigned int xms)
{
	unsigned int i;
	while(xms--)
	{
		i=12000;
		while(i--);
	}
}

void EPD_W21_Init(void)
{
	EPD_W21_RST_0;		// Module reset
	delay_xms(30);//At least 10ms delay 
	EPD_W21_RST_1;
	delay_xms(150);//At least 10ms delay 


}

void EPD_init(void)
{	
			EPD_W21_Init();             //Electronic paper IC reset

			EPD_W21_WriteCMD(0x00);			// panel setting   PSR
			EPD_W21_WriteDATA(0xF3);			// RES1 RES0 REG KW/R     UD    SHL   SHD_N  RST_N	 0xFF=LUT from register,0xDF=LUT from OTP. (Default)
			EPD_W21_WriteDATA(0x0D);			// x x x VCMZ TS_AUTO TIGE NORG VC_LUTZ

			EPD_W21_WriteCMD(0x01);			// POWER SETTING   PWR
			EPD_W21_WriteDATA(0x03);			//  x x x x x x VDS_EN VDG_EN	
			EPD_W21_WriteDATA(0x10);			//  x x x VCOM_SLWE VGH[3:0]   VGH=20V, VGL=-20V	
			EPD_W21_WriteDATA(0x3F);			//  x x VSH[5:0]	VSH = 15V
			EPD_W21_WriteDATA(0x3F);			//  x x VSL[5:0]	VSL=-15V
			EPD_W21_WriteDATA(0x03);			//  OPTEN VDHR[6:0]  VHDR=3V

			EPD_W21_WriteCMD(0x03);			// POWER OFF sequence setting    PFS
			EPD_W21_WriteDATA(0x00);			// x x T_VDS_OFF[1:0] x x x x 	
							// T_VDS_OFF[1:0] 00=1 frame; 01=2 frame; 10=3 frame; 11=4 frame

			EPD_W21_WriteCMD(0x06);			// booster soft start   BTST 
			EPD_W21_WriteDATA(0x0F);			//  BT_PHA[7:0]  	
			EPD_W21_WriteDATA(0x0F);			//  BT_PHB[7:0]	
			EPD_W21_WriteDATA(0x0F);			//  x x BT_PHC[5:0]	

			EPD_W21_WriteCMD(0x41);			// TEMPERATURE SENSOR ENABLE (TSE)
			EPD_W21_WriteDATA(0x00);			//  This command selects Internal or External temperature sensor.	

			EPD_W21_WriteCMD(0x2A);			// LUT Option LUTOPT
			EPD_W21_WriteDATA(0x00);			// EOTP ESO x x x x x x
			EPD_W21_WriteDATA(0x00);			// STATE_XON[7:0]  	
			EPD_W21_WriteDATA(0x00);			// STATE_XON[15:8]
			EPD_W21_WriteDATA(0xFF);			// GROUP_KWE[7:0]
			EPD_W21_WriteDATA(0x00);			// x x x x x ATRED NORED

			EPD_W21_WriteCMD(0x30);			// pll control  	PLL 
			EPD_W21_WriteDATA(0x09);			// x x x x FRS[4:0]  	frame rate = 50HZ-0x09

			EPD_W21_WriteCMD(0x50);			// VCOM and Data interval setting 	CDI 
			EPD_W21_WriteDATA(0xB7);			// VBD[1:0] DDX[1:0] CDI[3:0]

			EPD_W21_WriteCMD(0x60);			// TCON setting			TCON 
			EPD_W21_WriteDATA(0x22);			// S2G[3:0] G2S[3:0]   non-overlap = 12		

			EPD_W21_WriteCMD(0x61);			// resoultion setting 
			EPD_W21_WriteDATA(0xF0);			//  HRES[7:3] 0 0 0	
			EPD_W21_WriteDATA(0x01);			//  x x x x x x x VRES[8]	
			EPD_W21_WriteDATA(0x68);			//  VRES[7:0]

			EPD_W21_WriteCMD(0x65);			// gate/source start setting 	GSST
			EPD_W21_WriteDATA(0x00);			//  HST[7:3] 0 0 0	
			EPD_W21_WriteDATA(0x00);			//  x x x x x x x VST[8]	
			EPD_W21_WriteDATA(0x00);			//  VST[7:0]		

			EPD_W21_WriteCMD(0x82);			// VCOM_DC setting		VDCS 
			EPD_W21_WriteDATA(0x07);			// x  VDCS[6:0]	VCOM_DC value= -1.9v    00~3f,0x12=-1.9v

			EPD_W21_WriteCMD(0xE0);			// CASCADE SETTING (CCSET) 
			EPD_W21_WriteDATA(0x00);			// 

			EPD_W21_WriteCMD(0xE3);			// power saving			PWS 
			EPD_W21_WriteDATA(0x00);			// VCOM_W[3:0] SD_W[3:0]

			EPD_W21_WriteCMD(0xE4);			// Command  LVD Voltage Select 00:<2.2V  01:<2.3V  10:<2.4V  11:<2.5V 
			EPD_W21_WriteDATA(0x03);			// 

			EPD_W21_WriteCMD(0xE5);			// Command  Force Temperature
			EPD_W21_WriteDATA(0x00);			// 

			EPD_LUT(); //LUT settings

			delay_xms(200);	

}
void EPD_LUT(void)
	
{
unsigned int count;	 
	{
		EPD_W21_WriteCMD(0x20);							//vcom
		for(count=0;count<42;count++)
			{EPD_W21_WriteDATA(lut_vcom[count]);}
		
	  EPD_W21_WriteCMD(0x21);							//red not use
	  for(count=0;count<42;count++)
		  {EPD_W21_WriteDATA(lut_ww[count]);}

		EPD_W21_WriteCMD(0x22);							//bw r
		for(count=0;count<42;count++)
			{EPD_W21_WriteDATA(lut_bw[count]);}

		EPD_W21_WriteCMD(0x23);							//wb w
		for(count=0;count<42;count++)
			{EPD_W21_WriteDATA(lut_wb[count]);}

		EPD_W21_WriteCMD(0x24);							//bb b
		for(count=0;count<42;count++)
			{EPD_W21_WriteDATA(lut_bb[count]);}

	}	         
}
void EPD_sleep(void)
{
		EPD_W21_WriteCMD(0x07);  	//deep sleep
		EPD_W21_WriteDATA(0xA5);
}

void PIC_Image(const unsigned char* picData)
{
    unsigned int i;
	  //Write Data
//		EPD_W21_WriteCMD(0x10);	       //Transfer old data
//	  for(i=0;i<10800;i++)	  
//    {	
//	  EPD_W21_WriteDATA(0xff); 
//    }	
		EPD_W21_WriteCMD(0x13);		     //Transfer new data
	  for(i=0;i<10800;i++)	     
	  {
	  EPD_W21_WriteDATA(*picData);  //Transfer the actual displayed data
	  picData++;
	  }
	 //Refresh
		EPD_W21_WriteCMD(0x04);
		lcd_chkstatus();
		EPD_W21_WriteCMD(0x12);
		lcd_chkstatus();
		EPD_W21_WriteCMD(0x02);
}
void lcd_chkstatus(void)
{
	unsigned char busy;
	while(1)
		{
 
			busy = isEPD_W21_BUSY;
			if(busy!=0) break;        
		}
                       
}
void EPD_refresh(void)
{
	  EPD_W21_WriteCMD(0x04);			//power on 		
	  lcd_chkstatus();
		EPD_W21_WriteCMD(0x12);			//DISPLAY REFRESH 	
	
	
	
		delay_xms(100);	    //!!!The delay here is necessary, 200uS at least!!!     
		lcd_chkstatus();
}	
void PIC_display(unsigned char NUM)
{
	
	
 unsigned int row, column;
 unsigned int pcnt;

  pcnt = 0;    
	
	EPD_W21_WriteCMD(0x13);		     //Transfer new data
	
  for(column=0; column<Gate_Pixel; column++)   
  {
    for(row=0; row<Source_Pixel/8; row++)  
    {
      switch (NUM)
      {
        case PIC_WHITE:
          EPD_W21_WriteDATA(0xFF);
          break;  
				
        case PIC_BLACK:
          EPD_W21_WriteDATA(0x00);
          break;  
	                     
        default:
          break;
      }
    }
  }	
		 //Refresh
		EPD_W21_WriteCMD(0x04);
		lcd_chkstatus();
		EPD_W21_WriteCMD(0x12);
		lcd_chkstatus();
		EPD_W21_WriteCMD(0x02);
}

