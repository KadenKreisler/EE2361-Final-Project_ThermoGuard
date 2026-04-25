/*
 * File:   ThermoGaurd_main_v001.c
 * Authors: Kaden, Reid, Justin, Ben
 *
 * Created on April 6, 2026
 */

#include "xc.h"
#include "LCD_functions.h"
#include "LCD_base_library.h"
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




// ================= SETUP =================
void setup(void)
{
    CLKDIVbits.RCDIV = 0;   // 16 MHz FCY
    AD1PCFG = 0xFFFF;

 
    mainConfig();
    lcd_reset();
    lcd_init();

    init_tmr1();   // needed for LCD timing system

    temp_init();

    // temp pin default
    LATBbits.LATB13 = 0;
    TRISBbits.TRISB13 = 1;
}

// ================= MAIN =================
int main(void)
{
    setup();

    double temperature = 0;
    double temperatureF = 0;

    while(1)
    {
        __delay_ms(5);   // small system tick

        temp_update();   // non-blocking

        if(temp_ready())
        {
          temperature = get_TempC();
          temperatureF = (temperature * 9.0 / 5.0) + 32.0;
        }

        char tempStr[20];
        sprintf(tempStr, "%6.2f F", temperatureF);

        char xStr[20];
        sprintf(xStr, "X:%4d", temperature);

        char yStr[20];
        sprintf(yStr, "Y:%4d", temperature);

        char pirStr[20];
        sprintf(pirStr, "P:%d", temperature);

        print(tempStr, xStr, yStr, pirStr);
    }

    return 0;
}