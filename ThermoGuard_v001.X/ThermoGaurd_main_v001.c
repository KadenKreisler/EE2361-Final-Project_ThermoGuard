/*
 * File:   ThermoGaurd_main_v001.c
 * Authors: Kaden, Reid, Justin, Ben
 *
 * Created on April 6, 2026, 4:42 PM
 */

#include "xc.h"
#include "ThermoGaurd_Joystick_v001.h"
#include "ThermoGaurd_PIR_v001.h"
#include "ThermoGaurd_Servo_v001.h"
#include "LCD_base_library.h"
#include "LCD_functions.h"
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

volatile int X_val = 0;
volatile int Y_val = 0;
volatile int b1 = 1;
volatile int PIR = 0;

double temperature = 0;
double temperatureF = 0;

//This interrupt acts as the update for the joystick analong inputs as it only
//updates each time both finish converting.
void __attribute__((interrupt, auto_psv)) _ADC1Interrupt(void)
{
    IFS0bits.AD1IF = 0; 
    
    X_val = joystick_getX();
    Y_val = joystick_getY();
}

//This is the setup function which initializes each library used.
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
}

int main(void) {
    setup();

    while(1)
    {
        __delay_ms(5);   // small system tick

        temp_update();
        PIR = PIR_GetData();
        
        //This checks if the temp sensor has finished converting its data
        if(temp_ready())
        {
          temperature = get_TempC();
          temperatureF = (temperature * 9.0 / 5.0) + 32.0;
        }

        LCD_updateInputs(X_val, Y_val, b1, PIR, temperatureF);
        LCD_function_main();
    }
    
    return 0;
}
