20210319£ºThe following are the functions that need to be updated for IC upgrade£º

1.Full brush initialization, need to reset three times
void EPD_W21_Init(void)
{
	EPD_W21_RST_0;		// Module reset
	delay_xms(10);//At least 10ms delay 
	EPD_W21_RST_1;
	delay_xms(10);//At least 10ms delay 

	EPD_W21_RST_0;		// Module reset
	delay_xms(10);//At least 10ms delay 
	EPD_W21_RST_1;
	delay_xms(10);//At least 10ms delay 

	EPD_W21_RST_0;		// Module reset
	delay_xms(10);//At least 10ms delay 
	EPD_W21_RST_1;
	delay_xms(10);//At least 10ms delay 
	
}
2.Full brush function
//UC8151D   212x104
void EPD_init(void)
{	
		EPD_W21_Init(); //Electronic paper IC reset
    
		EPD_W21_WriteCMD(0x04);  
		lcd_chkstatus();//waiting for the electronic paper IC to release the idle signal

		EPD_W21_WriteCMD(0x00);			//panel setting
		EPD_W21_WriteDATA(0x1f);		//LUT from OTP¡ê?KW-BF   KWR-AF	BWROTP 0f	BWOTP 1f

		EPD_W21_WriteCMD(0x61);			//resolution setting
		EPD_W21_WriteDATA (0x68);  //104    	 
		EPD_W21_WriteDATA (0x00);  //212		
		EPD_W21_WriteDATA (0xd4);	
	
		EPD_W21_WriteCMD(0X50);			//VCOM AND DATA INTERVAL SETTING			
		EPD_W21_WriteDATA(0x97);		//WBmode:VBDF 17|D7 VBDW 97 VBDB 57		WBRmode:VBDF F7 VBDW 77 VBDB 37  VBDR B7
}

