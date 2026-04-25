/*
 * ThermoGuard Main
 * Fully integrated system
 */

#include "xc.h"
#include "ThermoGaurd_Joystick_v001.h"
#include "ThermoGaurd_PIR_v001.h"
#include "LCD_base_library.h"
#include "LCD_functions.h"
#include "TempSen.h"

// ================= CONFIG =================
#pragma config ICS = PGx1
#pragma config FWDTEN = OFF
#pragma config GWRP = OFF
#pragma config GCP = OFF
#pragma config JTAGEN = OFF

#pragma config I2C1SEL = PRI
#pragma config IOL1WAY = OFF
#pragma config OSCIOFNC = ON
#pragma config FCKSM = CSECME
#pragma config FNOSC = FRCPLL

volatile int X = 0;
volatile int Y = 0;
volatile int b1 = 1;   // button (pull-up, default HIGH)
volatile int PIR = 0;

double temperature = 0;
double temperatureF = 0;


void __attribute__((__interrupt__, auto_psv)) _ADC1Interrupt(void)
{
    IFS0bits.AD1IF = 0;

    X = joystick_getX();
    Y = joystick_getY();

    b1 = PORTBbits.RB12;   // joystick button
    PIR = PORTBbits.RB5;   // PIR sensor
}


void setup(void)
{
    CLKDIVbits.RCDIV = 0;   // 16 MHz FCY
    AD1PCFG = 0xFFFF;

    Joystick_init();
    PIR_init();

    mainConfig();   // I2C
    lcd_reset();
    lcd_init();

    init_tmr1();    // needed for LCD timing


    temp_init();    // non-blocking temp system

    // temp pin idle state
    LATBbits.LATB13 = 0;
    TRISBbits.TRISB13 = 1;
}


int main(void)
{
    setup();

    while(1)
    {
        __delay_ms(5);   // small system tick

        temp_update();

        if(temp_ready())
        {
          temperature = get_TempC();
          temperatureF = (temperature * 9.0 / 5.0) + 32.0;
        }

        LCD_updateInputs(X, Y, b1, temperatureF);
        LCD_function_main();
    }

    return 0;
}