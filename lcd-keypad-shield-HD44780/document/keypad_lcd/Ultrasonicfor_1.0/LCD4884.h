/*
Modified by Lauren
version 0.2

Any suggestions are welcome.
E-mail: Lauran.pan@gmail.com

=¡£=

* Have the back light under control.

*/

#ifndef LCD4884_h
#define LCD4884_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
  #else
  #include "WProgram.h"
  #endif

#define SPI_SCK 2
#define SPI_MOSI 3
#define LCD_DC  4
#define SPI_CS  5
#define LCD_RST 6
#define LCD_BL  7


//display mode -- normal / highlight
#define MENU_NORMAL	0
#define MENU_HIGHLIGHT 1
#define OFF 0
#define ON 1


class LCD4884
{
public:
LCD4884();
void LCD_init(void);
void backlight(unsigned char dat);
void LCD_write_byte(unsigned char dat, unsigned char dat_type);
void LCD_draw_bmp_pixel(unsigned char X,unsigned char Y,unsigned char *map,unsigned char Pix_x,unsigned char Pix_y);
void LCD_write_string(unsigned char X,unsigned char Y,char *s, char mode);      
void LCD_write_chinese(unsigned char X, unsigned char Y,unsigned char *c,unsigned char ch_with,unsigned char num,unsigned char line,unsigned char row);
void LCD_write_string_big ( unsigned char X,unsigned char Y, char *string, char mode );
void LCD_write_char_big (unsigned char X,unsigned char Y, unsigned char ch, char mode);
void LCD_write_char(unsigned char c, char mode);
void LCD_set_XY(unsigned char X, unsigned char Y);
void LCD_clear(void);
};
extern LCD4884 lcd;   
              
#endif   // 
