/*
 * File:   ThermoGaurd_main_v001.c
 * Authors: Kaden, Reid, Justin, Ben
 *
 * Created on April 6, 2026, 4:42 PM
 */

#include "xc.h"
#include "ThermoGaurd_Joystick_v001.h"
#include "ThermoGaurd_PIR_v001.h"
#include "LCD_functions.h"
#include "LCD_base_library.h"
#include "TempSen.h"

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

//Test code for PIR and joystick

int X_val;
int Y_val;
int b1;
int PIR;

void __attribute__ ((__interrupt__)) _ADC1Interrupt(void)
{
    IFS0bits.AD1IF = 0; 
    
    X_val = joystick_getX();
    Y_val = joystick_getY();

    b1 = PORTBbits.RB12;

    PIR = PORTBbits.RB5;
}

void init_Servo(void) {

   TRISBbits.TRISB11 = 0; // Sets output compare pin
   
   // Setup for input capture and output compare
    __builtin_write_OSCCONL(OSCCON & 0xbf);
    RPOR5bits.RP11R = 18;  
    __builtin_write_OSCCONL(OSCCON | 0x40);
   
 
    // Set up Timer 3
    T3CON = 0;
    T3CONbits.TCKPS = 0b01;
    TMR3 = 0;
    PR3 = 39999;
   
   
    // Output compare setup
    OC1CON = 0;
    OC1CONbits.OCTSEL = 1;
    OC1CONbits.OCM = 6;

    // Starts Timer 3
    T3CONbits.TON = 1;
}


// sets servo to position indicated by val, ranging from 1000 to 4000
    void setServo(int val)
    {
        OC1RS = val;
    }

void setup(void)
{
    CLKDIVbits.RCDIV = 0;  //Set RCDIV=1:1 (default 2:1) 32MHz or FCY/2=16M
    //Setup Code goes here!
    
    AD1PCFG = 0xFFFF; 
 
    Joystick_init();
    
    PIR_init();
    
    mainConfig();
    lcd_reset();
    lcd_init();

    init_tmr1();

    temp_init();
    
    init_Servo();
    
    LATBbits.LATB13 = 0;
    TRISBbits.TRISB13 = 1;
}

int main(void) {
    setup();
  
    double temperature = 0;
    double temperatureF = 0;
    
    while(1)
    {
        __delay_ms(5);  
            
        if(b1 == 1)
        {
            setServo(1200);
        }
        
        temp_update();   // non-blocking
        
        if(temp_ready())
        {
          temperature = get_TempC();
          temperatureF = (temperature * 9.0 / 5.0) + 32.0;
        }


        char tempStr[20];
        sprintf(tempStr, "%6.4f F", temperatureF);

        char temp1Str[20];
        sprintf(temp1Str, "%4d", X_val);

        char temp2Str[20];
        sprintf(temp2Str, "%4d", Y_val);

        char temp3Str[20];
        sprintf(temp3Str, "%d", PIR);

        print(
                tempStr,
                temp1Str,
                temp2Str,
                temp3Str
            );
    }
    
    return 0;
}
