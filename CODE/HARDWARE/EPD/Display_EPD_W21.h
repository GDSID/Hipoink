#ifndef _DISPLAY_EPD_W21_H_
#define _DISPLAY_EPD_W21_H_


#define EPD_WIDTH   240
#define EPD_HEIGHT  360

//#define OTP_Mode             // 
#define Normal_TEST            //
//#define Auto_RUN             //
//#define Partial_Display      //
//#define GUI_Display          //

#define PIC_WHITE                     0xFF  // 
#define PIC_BLACK                     0x00  //
#define PIC_Source_Line               0xAA  //
#define PIC_Gate_Line                 0x55  //
#define PIC_UP_BLACK_DOWN_WHITE       0xF0  //
#define PIC_LEFT_BLACK_RIGHT_WHITE    0x0F  //
#define PIC_Frame                     0x01  // 
#define PIC_Crosstalk                 0x02  //
#define PIC_Chessboard                0x03  //


extern unsigned char HRES,VRES_byte1,VRES_byte2;


//EPD
void EPD_W21_Init(void);
void EPD_init(void);
void EPD_init_data(void);

void EPD_OTP(void);
void EPD_LUT(void);


void EPD_partial_display_Full(unsigned int x_start,unsigned int y_start,const unsigned char *new_data,unsigned int PART_COLUMN,unsigned int PART_LINE,unsigned char mode); //partial display 

void EPD_sleep(void);
void EPD_refresh(void);
void lcd_chkstatus(void);
void PIC_display_Clear(void);
//Display canvas function
void PIC_display(unsigned char NUM);
void EPD_Display(unsigned char *Image); 
void PIC_Image(const unsigned char* picData);



#endif
/***********************************************************
						end file
***********************************************************/


