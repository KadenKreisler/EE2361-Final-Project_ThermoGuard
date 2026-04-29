/*
 * File:   ThermoGaurd_Servo_v001.c
 * Author: Kaden
 *
 * Created on April 28, 2026, 12:35 AM
 */


#include "xc.h"
#include "ThermoGaurd_Servo_v001.h"

//This function initializes the output capture, timer 2, and pin used to control the servo.
void init_Servo(void)
{
   TRISBbits.TRISB12 = 0; // Sets output compare pin
   
   // Setup for input capture and output compare
    __builtin_write_OSCCONL(OSCCON & 0xbf);
    RPOR6bits.RP12R = 18;  
    __builtin_write_OSCCONL(OSCCON | 0x40);
  
    T2CON = 0;
    T2CONbits.TCKPS = 0b01;   // 1:8 prescaler
    TMR2 = 0;
    PR2 = 40000;              // 20ms period
   
    // Output compare setup
    OC1CON = 0;
    OC1CONbits.OCTSEL = 0;    // Timer2
    OC1CONbits.OCM = 0b110;   // PWM mode
    
    OC1R = 3000;
    OC1RS = 3000;

    // Starts Timer 3
    T2CONbits.TON = 1;
}

//This function is used to set the position of the servo
void setServo(int val)
{
    OC1RS = val;
}