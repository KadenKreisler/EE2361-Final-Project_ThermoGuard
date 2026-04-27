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

void servo_init(void)
{
    
    __builtin_write_OSCCONL(OSCCON & 0xBF);   // unlock PPS

    RPOR3bits.RP7R = 18;   // OC1 ? RP7 (RB7)

    __builtin_write_OSCCONL(OSCCON | 0x40);   // lock PPS

    TRISBbits.TRISB7 = 0;  // RB7 output
    
    T2CON = 0;
    T2CONbits.TCKPS = 0b01;   // 1:8 prescaler
    PR2 = 40000;              // 20ms period

    OC1CON = 0;
    OC1CONbits.OCTSEL = 0;    // Timer2
    OC1CONbits.OCM = 0b110;   // PWM mode

    OC1R = 3000;
    OC1RS = 3000;

    T2CONbits.TON = 1;
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
    
    servo_init();

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
        int pir = PIR_GetData();
        if(temp_ready())
        {
          temperature = get_TempC();
          temperatureF = (temperature * 9.0 / 5.0) + 32.0;
        }

        LCD_updateInputs(X, Y, b1, pir, temperatureF);
        LCD_function_main();
    }

    return 0;
}