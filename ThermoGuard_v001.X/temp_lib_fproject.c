/*
 * File:   temp_lib.c
 * Author: jsspi
 *
 * Created on April 13, 2026, 11:58 PM
 */


#include "xc.h"
#include <stdint.h>
#include <stdio.h> 
#define FCY 16000000UL
#include <libpic30.h> 
// #include "lcd_proj.h"
// CW1: FLASH CONFIGURATION WORD 1 (see PIC24 Family Reference Manual 24.1)
#pragma config ICS = PGx1          // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config FWDTEN = OFF        // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config GWRP = OFF          // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF           // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF        // JTAG Port Enable (JTAG port is disabled)
   



// CW2: FLASH CONFIGURATION WORD 2 (see PIC24 Family Reference Manual 24.1)
#pragma config I2C1SEL = PRI       // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = OFF       // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
#pragma config OSCIOFNC = ON       // Primary Oscillator I/O Function (CLKO/RC15 functions as I/O pin)
#pragma config FCKSM = CSECME      // Clock Switching and Monitor (Clock switching is enabled, 
// Fail-Safe Clock Monitor is enabled)
#pragma config FNOSC = FRCPLL      // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))
int detection = 0;
  double var = 0;
    char data[9];




int temp_reset(void) {
    detection = 0;
    low();
   __delay_us(480);
    release();
  __delay_us(70);
    if(PORTBbits.RB13 == 0) {
      detection = 1;
        
    }
   __delay_us(410);
    
    return detection;

}


void low() {
        LATBbits.LATB13 = 0;
       TRISBbits.TRISB13 = 0;
  

}

void release() {
    
  
  
      LATBbits.LATB13 = 0;
    TRISBbits.TRISB13 = 1;

    
}

void write_0() {
    
    low();
 __delay_us(60);
    release();
    __delay_us(5);

 
}

void write_1() {
    
    low();
   __delay_us(5);
    release();
    __delay_us(55);
   
}




int read_bit() {
    int value = 0;
    low();
    __delay_us(3);
    release();
   __delay_us(5);
    if(PORTBbits.RB13 == 1) {
        value = 1;
        
    }
    
    
   __delay_us(55);
    return value;
}

int read_byte() {
    int byte_2 = 0;
    int bit;
    for(int i = 0; i < 8; i++) {
      bit = read_bit();
      if(bit) {
         
          byte_2 |= (1 << i);
      }
        
   
    }
    
    return byte_2;
    
}




void write_byte(char byte_1) {

    
    for(int i = 0; i < 8; i++) {
        if(byte_1 & 0x01) {
            write_1();
            
            
        }
        else
        {
            write_0();
        }
        
        byte_1 >>=1;
    }
    
}

int init_Temp() {
    
    if(!temp_reset()) {
        return 0;
    }
    
    write_byte(0xCC);
    write_byte(0x4E);
    write_byte(0x7D);
   write_byte(0x00);
   write_byte(0x7F);
  if(!temp_reset()) {
        return 0;
    }
    write_byte(0xCC);
    write_byte(0x48); 
    __delay_ms(10);
   
    return 1;
}


    



double get_TempC() {
    double temperature = 0;
  
      if ( !temp_reset() ) {
          return -999;
          
      }
       write_byte(0xCC);
       write_byte(0x44);
       
  __delay_ms(400);
       
       if ( !temp_reset() ) {
          return -999;
          
      }
              write_byte(0xCC);
       write_byte(0xBE);
           
       
       __delay_us(10);
     
     for(int i = 0; i < 9; i++ ){
        data[i] = read_byte();
        
    }

       
          
       
     
       
       uint16_t lsByte = data[0];
       uint16_t msByte = data[1];
       int16_t tempWord = 0x0000;
      tempWord = msByte;
               tempWord <<= 8;
       tempWord |= lsByte ;
       
       temperature = tempWord / 16.0;
       
   
       

             return temperature;

 
    
    
}





/*
int main() {
     CLKDIVbits.RCDIV =0; // set clock
    AD1PCFG = 0xFFFF;
   
   
      setup(); 
  lcd_reset();
    lcd_init();
  lcd_setCursor(0,0);
 
 
    LATBbits.LATB13 = 0;
    TRISBbits.TRISB13 = 1;
    
    
  
   if(!init_Temp()) {
       
       lcd_printStr("FAIL");
       return -1;
   }
  
    
    
    while(1)
    {
      
      
      var = get_TempC(); 
     int varia = var; 
       char adStr[20];
      sprintf(adStr, "%6.4f C", var);
       lcd_printStr(adStr);
    }
    
    
    
    return 0;

 }
 */