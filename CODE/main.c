
#define Source_Pixel  240      
#define Gate_Pixel    360    


#define PIC_WHITE     0xFF  
#define PIC_BLACK     0x00  


void EPD_init(void);
void PIC_display(unsigned char NUM);
void PIC_display1(const unsigned char* picData);

void EPD_sleep(void);
void EPD_refresh(void);
void lcd_chkstatus(void);

void KEY_Scan(void);  	//按键扫描函数
void EPD_partial_display_Full(u16 x_start,u16 y_start,const unsigned char *new_data,unsigned int PART_COLUMN,unsigned int PART_LINE,unsigned char mode); //partial display 

void lut_DU(void);
///////////////////////////////////////

int	main(void)
{
while(1)
     {	

				EPD_Reset();                //Electronic paper IC reset			 
        PIC_display1(gImage_1);     //EPD_picture
				EPD_refresh();	            //Auto Sequence
        EPD_sleep();			          //进入睡眠后退出要进行复位
        KEY_Scan();		
	
				EPD_Reset();                //Electronic paper IC reset			 
        PIC_display1(gImage_2);     //EPD_picture
				EPD_refresh();	            //Auto Sequence
        EPD_sleep();			          //进入睡眠后退出要进行复位
        KEY_Scan();	
	
				EPD_Reset();                //Electronic paper IC reset		
				PIC_display(PIC_WHITE);     //EPD_picture
				EPD_refresh();	
        EPD_sleep();			          //进入睡眠后退出要进行复位				
        KEY_Scan();			 
			 

///*********************************************************/		

				EPD_partial_display_Full(0,196,gImage_num[5],32,32,0);  //x,y,old_data,new_data,W,L,mode
				DELAY_S(2);		
				EPD_partial_display_Full(0,228,gImage_num[6],32,32,0);  //x,y,old_data,new_data,W,L,mode
				DELAY_S(2);		
				EPD_partial_display_Full(0,260,gImage_num[7],32,32,0);  //x,y,old_data,new_data,W,L,mode
				DELAY_S(2);		
				EPD_partial_display_Full(0,292,gImage_num[8],32,32,0);  //x,y,old_data,new_data,W,L,mode
				DELAY_S(2);		
				EPD_partial_display_Full(0,324,gImage_num[9],32,32,0);  //x,y,old_data,new_data,W,L,mode
				DELAY_S(2);	
	
				EPD_partial_display_Full(112,32,gImage_num[8],32,32,0);  //x,y,old_data,new_data,W,L,mode
				DELAY_S(2);	
				EPD_partial_display_Full(112,64,gImage_num[7],32,32,0);  //x,y,old_data,new_data,W,L,mode
				DELAY_S(2);					
				EPD_partial_display_Full(112,96,gImage_num[6],32,32,0);  //x,y,old_data,new_data,W,L,mode
				DELAY_S(2);	
				EPD_partial_display_Full(112,128,gImage_num[5],32,32,0);  //x,y,old_data,new_data,W,L,mode
				DELAY_S(2);	


				KEY_Scan();	

		}
}		

void EPD_init(void)
{

#if 1

	EPD_W21_WriteCMD(0x00);			// panel setting   PSR
	EPD_W21_WriteDATA(0xFF);			// RES1 RES0 REG KW/R     UD    SHL   SHD_N  RST_N	
	EPD_W21_WriteDATA(0x01);			// x x x VCMZ TS_AUTO TIGE NORG VC_LUTZ
	
	EPD_W21_WriteCMD(0x01);			// POWER SETTING   PWR
	EPD_W21_WriteDATA(0x03);			//  x x x x x x VDS_EN VDG_EN	
	EPD_W21_WriteDATA(0x10);			//  x x x VCOM_SLWE VGH[3:0]   VGH=20V, VGL=-20V	
	EPD_W21_WriteDATA(0x3F);			//  x x VSH[5:0]	VSH = 15V
	EPD_W21_WriteDATA(0x3F);			//  x x VSL[5:0]	VSL=-15V
	EPD_W21_WriteDATA(0x03);			//  OPTEN VDHR[6:0]  VHDR=6.4V
 								              // T_VDS_OFF[1:0] 00=1 frame; 01=2 frame; 10=3 frame; 11=4 frame
	EPD_W21_WriteCMD(0x06);			// booster soft start   BTST 
	EPD_W21_WriteDATA(0x37);			//  BT_PHA[7:0]  	
	EPD_W21_WriteDATA(0x3D);			//  BT_PHB[7:0]	
	EPD_W21_WriteDATA(0x3D);			//  x x BT_PHC[5:0]	
	
	EPD_W21_WriteCMD(0x60);			// TCON setting			TCON 
	EPD_W21_WriteDATA(0x22);			// S2G[3:0] G2S[3:0]   non-overlap = 12		

	EPD_W21_WriteCMD(0x82);			// VCOM_DC setting		VDCS 
	EPD_W21_WriteDATA(0x07);			// x  VDCS[6:0]	VCOM_DC value= -1.9v    00~3f,0x12=-1.9v

	EPD_W21_WriteCMD(0x30);			 
	EPD_W21_WriteDATA(0x09);		
	
	EPD_W21_WriteCMD(0xe3);			// power saving			PWS 
	EPD_W21_WriteDATA(0x88);			// VCOM_W[3:0] SD_W[3:0]

	EPD_W21_WriteCMD(0x61);			// resoultion setting 
	EPD_W21_WriteDATA(0xf0);			//  HRES[7:3] 0 0 0	
	EPD_W21_WriteDATA(0x01);			//  x x x x x x x VRES[8]	
	EPD_W21_WriteDATA(0x68);			//  VRES[7:0]
	
	EPD_W21_WriteCMD(0X50);      // 
	EPD_W21_WriteDATA(0xB7);     // Border
	
#endif		
	
}



void EPD_refresh(void)
{
	EPD_W21_WriteCMD(0x17);			//DISPLAY REFRESH 		
  EPD_W21_WriteDATA(0xA5);
	lcd_chkstatus();
	driver_delay_xms(200);
}	
void EPD_sleep(void)
{
		EPD_W21_WriteCMD(0X07);  	//deep sleep
		EPD_W21_WriteDATA(0xA5);
}



//LUT download
void lut_DU(void)
{
	unsigned int count;	 
	
		EPD_W21_WriteCMD(0x20);							//vcom
		for(count=0;count<56;count++)
			{EPD_W21_WriteDATA(lut_R20_DU[count]);}
		
	  EPD_W21_WriteCMD(0x21);							//red not use
	  for(count=0;count<42;count++)
		  {EPD_W21_WriteDATA(lut_R21_DU[count]);}

		EPD_W21_WriteCMD(0x24);							//bb b
		for(count=0;count<56;count++)
			{EPD_W21_WriteDATA(lut_R24_DU[count]);}			

	  EPD_W21_WriteCMD(0x22);							//bw r
		for(count=0;count<56;count++)
			{EPD_W21_WriteDATA(lut_R22_DU[count]);}

		EPD_W21_WriteCMD(0x23);							//wb w
		for(count=0;count<56;count++)
			{EPD_W21_WriteDATA(lut_R23_DU[count]);}

	 			         
}



void PIC_display1(const unsigned char* picData)
{
    unsigned int i;
	
		EPD_W21_WriteCMD(0x13);		     //Transfer new data
		for(i=0;i<(Gate_Pixel*Source_Pixel/8);i++)	     
				{
					EPD_W21_WriteDATA(*picData);
					picData++;
				}	
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
	
}



void lcd_chkstatus(void)
{
	while(isEPD_W21_BUSY==0);   
	driver_delay_xms(200);                       
}

void KEY_Scan(void)
{	 

	unsigned char KEY;
	do
	{
		KEY = KEY0;
    	driver_delay_xms(2);	  
	}
	while(KEY);   
	driver_delay_xms(20);	
	 
}


void EPD_partial_display_Full(u16 x_start,u16 y_start,const unsigned char *new_data,unsigned int PART_COLUMN,unsigned int PART_LINE,unsigned char mode) //partial display 
{
unsigned int i,count;  
	unsigned int x_end,y_start1,y_start2,y_end1,y_end2;
	x_start=x_start;//转换为字节
	x_end=x_start+PART_LINE-1; 
	
	y_start1=0;
	y_start2=y_start;
	if(y_start>=256)
	{
		y_start1=y_start2/256;
		y_start2=y_start2%256;
	}
	y_end1=0;
	y_end2=y_start+PART_COLUMN-1;
	if(y_end2>=256)
	{
		y_end1=y_end2/256;
		y_end2=y_end2%256;		
	}		
	
  count=PART_COLUMN*PART_LINE/8;

/*********************************************************/	
//需要重新复位和初始化设置!!!!
/*********************************************************/	
    EPD_Reset();                //Electronic paper IC reset
/*********************************************************/		
	
		EPD_W21_WriteCMD(0x00);			// panel setting   PSR
	  EPD_W21_WriteDATA(0xFF);			// RES1 RES0 REG KW/R     UD    SHL   SHD_N  RST_N	
	  EPD_W21_WriteDATA(0x01);			// x x x VCMZ TS_AUTO TIGE NORG VC_LUTZ	
	
	  EPD_W21_WriteCMD(0x91);		//This command makes the display enter partial mode
		EPD_W21_WriteCMD(0x90);		//resolution setting
		EPD_W21_WriteDATA (x_start);   //x-start     
		EPD_W21_WriteDATA (x_end);	 //x-end	

		EPD_W21_WriteDATA (y_start1);
		EPD_W21_WriteDATA (y_start2);   //y-start    
		
		EPD_W21_WriteDATA (y_end1);		
		EPD_W21_WriteDATA (y_end2);  //y-end
		EPD_W21_WriteDATA (0x01);	
	
	
	if(mode==0)
	{
			EPD_W21_WriteCMD(0x13);				 //writes New data to SRAM.
				for(i=0;i<count;i++)	     
			 {
				EPD_W21_WriteDATA(new_data[i]); //图片  
			 }
  }
	else if(mode==1)
	{
				
		
			EPD_W21_WriteCMD(0x10);	       //writes Old data to SRAM for programming

				for(i=0;i<count;i++)	     
				{
				 EPD_W21_WriteDATA(0x00);  
				}			
		
			EPD_W21_WriteCMD(0x13);				 //writes New data to SRAM.
				for(i=0;i<count;i++)	     
			 {
				EPD_W21_WriteDATA(0xFF);  //全黑
			 }

  }		
	else if(mode==2)
	{
		
			EPD_W21_WriteCMD(0x10);	       //writes Old data to SRAM for programming

				for(i=0;i<count;i++)	     
				{
				 EPD_W21_WriteDATA(0xFF);  
				}			
		
			EPD_W21_WriteCMD(0x13);				 //writes New data to SRAM.
				for(i=0;i<count;i++)	     
			 {
				EPD_W21_WriteDATA(0x00);  //全黑
			 }

  }	 
	
			lut_DU();
			EPD_refresh();	
 	    driver_delay_xms(500); 
/*********************************************************/	
//需要重新复位和初始化设置!!!!
/*********************************************************/	
      EPD_Reset();                //Electronic paper IC reset
}



void EPD_Reset(void)
{
	EPD_W21_RST_1;
	driver_delay_xms(10);	//At least 10ms delay 
	EPD_W21_RST_0;		// Module reset
	driver_delay_xms(10);//At least 10ms delay 
	EPD_W21_RST_1;
	driver_delay_xms(50);	//At least 10ms delay 
	
	
	EPD_W21_WriteCMD(0x00);			// panel setting   PSR
	EPD_W21_WriteDATA(0xD7);		// 设置扫描方向
	
/***********************负载电阻使用2.2R***************************/	
	EPD_W21_WriteCMD(0x06);			// booster soft start   BTST 
	EPD_W21_WriteDATA(0x37);		//  BT_PHA[7:0]  	
	EPD_W21_WriteDATA(0x3D);		//  BT_PHB[7:0]	
	EPD_W21_WriteDATA(0x3D);		//  x x BT_PHC[5:0]		
	driver_delay_xms(10);	//At least 10ms delay	
	
}


void SPI_Delay(unsigned char xrate)
{
	unsigned char i;
	while(xrate)
	{
		for(i=0;i<EPD_W21_SPI_SPEED;i++);
		xrate--;
	}
}


void SPI_Write(unsigned char value)                                    
{                                                           
    unsigned char i;

	
	SPI_Delay(1);
    for(i=0; i<8; i++)   
    {
        EPD_W21_CLK_0;
		SPI_Delay(1);
        if(value & 0x80)
        	EPD_W21_MOSI_1;
        else
        	EPD_W21_MOSI_0;		
        value = (value << 1); 
		SPI_Delay(1);
		driver_delay_us(1);
        EPD_W21_CLK_1; 
        SPI_Delay(1);
    }
}



void EPD_W21_WriteCMD(unsigned char command)
{
    SPI_Delay(1);
    EPD_W21_CS_0;                   
	EPD_W21_DC_0;		// command write
	SPI_Write(command);
	EPD_W21_CS_1;
}
void EPD_W21_WriteDATA(unsigned char command)
{
    SPI_Delay(1);
    EPD_W21_CS_0;                   
	EPD_W21_DC_1;		// command write
	SPI_Write(command);
	EPD_W21_CS_1;
}


/***********************************************************
						end file
