
#ifndef LCD_BASE_LIBRARY_H
#define	LCD_BASE_LIBRARY_H


#include <xc.h> // include processor files - each processor file is guarded.  

#define FCY 16000000UL
#include <libpic30.h>  //for exact delay cmmands 


#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

  // Insert declarations
 void i2c_wait(void); 
 
 void lcd_cmd(char command); 
 
 void lcd_printChar(char myChar); 
 
void lcd_reset(void); 

void lcd_init(void); 

void lcd_setCursor(char x, char y); 


void lcd_printStr(const char *str); 

void mainConfig (void); 


#endif
