/*
 * File:   ThermoGaurd_main_v001.c
 * Authors: Kaden, Reid, Justin, Ben
 *
 * Created on April 6, 2026, 4:42 PM
 */

#include "xc.h"
#include "ThermoGaurd_Joystick_v001.h"
#include "ThermoGaurd_PIR_v001.h"

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
/*
int X;
int Y;
int b1;
int PIR;

void __attribute__ ((__interrupt__)) _ADC1Interrupt(void)
{
    IFS0bits.AD1IF = 0; 
    
    X = joystick_getX();
    Y = joystick_getY();

    b1 = PORTBbits.RB12;

    PIR = PORTBbits.RB5;
}
*/

void setup(void)
{
    CLKDIVbits.RCDIV = 0;  //Set RCDIV=1:1 (default 2:1) 32MHz or FCY/2=16M
    //Setup Code goes here!
    
    Joystick_init();
    PIR_init();
}

int main(void) {
    setup();
  
    
    while(1)
    {
    }
    
    return 0;
}
