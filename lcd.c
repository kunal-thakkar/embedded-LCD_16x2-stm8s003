#include "lcd.h"

/*--------------- Initialize LCD ------------------*/
void lcd_init(void)
{
    delay_ms(40);
    
    PIN_LOW(LCD_PORT,LCD_D4);
    PIN_HIGH(LCD_PORT,LCD_D5);
    PIN_LOW(LCD_PORT,LCD_D6);
    PIN_LOW(LCD_PORT,LCD_D7);
    PIN_LOW(LCD_PORT,LCD_RS);
    
    PIN_HIGH(LCD_PORT,LCD_EN);
    PIN_LOW(LCD_PORT,LCD_EN);
    
    lcd_write(0,0x28);
    lcd_write(0,0x0c);
    lcd_write(0,0x06);
    lcd_write(0,0x01);
}

/*--------------- Write To LCD ---------------*/
void lcd_write(uint8_t type,uint8_t data)
{
    delay_ms(2);
    if(type)
    {
        PIN_HIGH(LCD_PORT,LCD_RS);
    }else
    {
        PIN_LOW(LCD_PORT,LCD_RS);
    }
    
    //Send High Nibble
    if(data&0x80)
    {
        PIN_HIGH(LCD_PORT,LCD_D7);
    }else
    {
        PIN_LOW(LCD_PORT,LCD_D7);
    }
    
    if(data&0x40)
    {
        PIN_HIGH(LCD_PORT,LCD_D6);
    }else
    {
        PIN_LOW(LCD_PORT,LCD_D6);
    }
    
    if(data&0x20)
    {
        PIN_HIGH(LCD_PORT,LCD_D5);
    }else
    {
        PIN_LOW(LCD_PORT,LCD_D5);
    }
    
    if(data&0x10)
    {
        PIN_HIGH(LCD_PORT,LCD_D4);
    }else
    {
        PIN_LOW(LCD_PORT,LCD_D4);
    }
    PIN_HIGH(LCD_PORT,LCD_EN);
    PIN_LOW(LCD_PORT,LCD_EN);

    //Send Low Nibble
    if(data&0x08)
    {
        PIN_HIGH(LCD_PORT,LCD_D7);
    }else
    {
        PIN_LOW(LCD_PORT,LCD_D7);
    }
    
    if(data&0x04)
    {
        PIN_HIGH(LCD_PORT,LCD_D6);
    }else
    {
        PIN_LOW(LCD_PORT,LCD_D6);
    }
    
    if(data&0x02)
    {
        PIN_HIGH(LCD_PORT,LCD_D5);
    }else
    {
        PIN_LOW(LCD_PORT,LCD_D5);
    }
    
    if(data&0x01)
    {
        PIN_HIGH(LCD_PORT,LCD_D4);
    }else
    {
        PIN_LOW(LCD_PORT,LCD_D4);
    }
    PIN_HIGH(LCD_PORT,LCD_EN);
    PIN_LOW(LCD_PORT,LCD_EN);
}

void lcd_puts(uint8_t x, uint8_t y, int8_t *string)
{
    //Set Cursor Position
    #ifdef LCD16xN	//For LCD16x2 or LCD16x4
    switch(x)
    {
      case 0: //Row 0
          lcd_write(0,0x80+0x00+y);
          break;
      case 1: //Row 1
          lcd_write(0,0x80+0x40+y);
          break;
      case 2: //Row 2
          lcd_write(0,0x80+0x10+y);
          break;
      case 3: //Row 3
          lcd_write(0,0x80+0x50+y);
          break;
    }
    #endif
    #ifdef LCD20xN	//For LCD20x4
    switch(x)
    {
      case 0: //Row 0
          lcd_write(0,0x80+0x00+y);
          break;
      case 1: //Row 1
          lcd_write(0,0x80+0x40+y);
          break;
      case 2: //Row 2
          lcd_write(0,0x80+0x14+y);
          break;
      case 3: //Row 3
          lcd_write(0,0x80+0x54+y);
          break;
    }
    #endif
    while(*string)
    {
        lcd_write(1,*string);
        string++;
    }
}

void lcd_clear(void)
{
    lcd_write(0,0x01);
}
