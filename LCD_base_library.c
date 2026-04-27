
#include "xc.h"
#include "LCD_base_library.h"

#define FCY 16000000UL
#include <libpic30.h>  //for exact delay cmmands 

void i2c_wait(void)
{
    while (I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || 
           I2C1CONbits.RSEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT);
}
//for upper function, if SENDING, PTOP, RECCIEVE, RESTART, ACK, or STOP, block IC2 until finish 

void lcd_cmd(char command)
{
    i2c_wait(); 
    I2C1CONbits.SEN = 1; //trigger start of command sequence
    while(I2C1CONbits.SEN);
    
    _MI2C1IF = 0;
    I2C1TRN = 0x78;         // Slave Address
    while(!_MI2C1IF);
    
    _MI2C1IF = 0;
    I2C1TRN = 0x00;         // Command designator 
    while(!_MI2C1IF);
    
    _MI2C1IF = 0;
    I2C1TRN = command;      // command actual 
    while(!_MI2C1IF);
    
    I2C1CONbits.PEN = 1;
    while(I2C1CONbits.PEN); // wait for IC2 to actually halt 
}

void lcd_printChar(char myChar)
{
    i2c_wait();
    I2C1CONbits.SEN = 1;      //START 
    while(I2C1CONbits.SEN);   
    
    _MI2C1IF = 0;
    I2C1TRN = 0x78;         // Slave Address
    while(!_MI2C1IF);         
   
    _MI2C1IF = 0;
    I2C1TRN = 0x40;         //command designator: PRINT 
    while(!_MI2C1IF); //this checks if the master interrupt flag is set to 1; 0 = cmd not done yet 
    
    _MI2C1IF = 0;
    I2C1TRN = myChar;       //Character to PRINT 
    while(!_MI2C1IF);
    
    I2C1CONbits.PEN = 1;      
    while(I2C1CONbits.PEN); // STOP
}


void lcd_reset(void)
{
    TRISBbits.TRISB6 = 0;   // RB6 = RESET per lab manual schematic
    
    LATBbits.LATB6 = 0;    
    __delay_ms(10);         

    LATBbits.LATB6 = 1;     
    __delay_ms(50);       
}


void lcd_init(void)
{ 
    __delay_ms(50); 
//from lab background sequence 
    lcd_cmd(0x3A);  // RE=1
    lcd_cmd(0x09);
    lcd_cmd(0x06);  // Bottom view
    lcd_cmd(0x1E);  // BS1=1
    
    lcd_cmd(0x39);  // RE=0, IS=1 
    lcd_cmd(0x1B);  // OSC frequency
    lcd_cmd(0x6E);  // Follower control
    
    lcd_cmd(0x56);  // Booster ON / Contrast
    lcd_cmd(0x7A);  // Contrast , changed from A to F for more higher contrast 
    
    lcd_cmd(0x38);  // RE=0, IS=0 
    lcd_cmd(0x0F);  // Display ON, Cursor ON, Blink ON
    lcd_cmd(0x01);  // Clear 
    __delay_ms(5);  
}

void lcd_setCursor4rows(char x, char y)
{
    char address;

    if (y == 0)
    { 
        address = 0x00 + x;
    } 
    
    else if (y == 1)
    { 
        address = 0x20 + x; 
    } 
    else if (y == 2)
    { 
        address = 0x40 + x; 
    } 
    else if (y == 3)
    { 
        address = 0x60 + x; 
    } 
    else
    { 
        address = 0x00 + x; 
    } 
    
    lcd_cmd(0x80 | address);
}


//for debug pruposes, const char prevents string from changing
void lcd_printStr(const char *str)
{
    while (*str != '\0')
    { 
        lcd_printChar(*str); 
        str++; 
    }
}

void mainConfig (void)
{ 
    TRISBbits.TRISB8 = 1; // SCL1 - establishes "constant comms"
    TRISBbits.TRISB9 = 1; // SDA1 - sends data back and forth

    I2C1CONbits.I2CEN = 0;
    IFS1bits.MI2C1IF = 0;
    I2C1BRG = 157;           // 100kHz at 16 MHz Fcy 
    //formula: (Fcy/Fcl) - Fcy/10,000,000 - 1 
    
    I2C1CONbits.I2CEN = 1;   
}



