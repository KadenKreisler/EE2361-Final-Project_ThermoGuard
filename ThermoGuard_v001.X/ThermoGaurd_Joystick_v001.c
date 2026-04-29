/*
 * File:   ThermoGaurd_Joystick_v001.c
 * Author: Kaden
 *
 * Created on April 15, 2026, 1:46 AM
 */


#include "xc.h"
#include "ThermoGaurd_Joystick_v001.h"

//This function initializes the joystick pins and sets up the analog registers
//and configures the interrupt to happen after 2 conversions 
void Joystick_init()
{
    //AN4 and AN5
    AD1PCFGbits.PCFG4 = 0; //sets pin RB4 to analog
    TRISBbits.TRISB2 = 1; //sets pin RB4 to input
    
    AD1PCFGbits.PCFG5 = 0; //sets pin RB5 to analog
    TRISBbits.TRISB2 = 1; //sets pin RB5 to input
    
//    1. Configure the A/D module:

    AD1CON1bits.SSRC = 0b111; // auto-convert
    AD1CON1bits.ASAM = 1; //continously sample
    AD1CON1bits.FORM = 0b00; //unsigned int
    
    AD1CON2bits.ALTS = 0; // Does not alternate between MUX A and B
    AD1CON2bits.VCFG = 0b000; // sets the voltage range to VDD to VSS 
    AD1CON2bits.SMPI = 1; // interupts at every 2 convertion complete, ex AN0 and AN1
    AD1CON2bits.CSCNA = 1; //Scans the channels in the CSSL register
    //Ex. AN0 and AN1 like configured below
    
    AD1CSSLbits.CSSL4 = 1; // AN4
    AD1CSSLbits.CSSL5 = 1; // AN5
   
    AD1CON3bits.ADCS = 1; // TAD of 125ns
    
//    2. Configure A/D interrupt:
    IFS0bits.AD1IF = 0; // Clear A/D conversion interrupt.
    IEC0bits.AD1IE = 1; // Enable A/D conversion interrupt

//    3. Turn on A/D module.
    AD1CON1bits.ADON = 1;
    
    
    //Something for the button part of the joystick - not setup yet
    
    CNPU1bits.CN14PUE = 1;  // RB12
    
    AD1PCFG |= 0b0001000000000000; //Sets pin RB12 digital
    TRISB |= 0b0001000000000000;   // Set pin RB12 as input
}

//This function gets the X axis value from analog buffer 0
int joystick_getX()
{
    return ADC1BUF4;
}

//This function gets the Y axis value from analog buffer 1
int joystick_getY()
{
    return ADC1BUF5;
}

//This function returns the state of the joystick PB
int joystick_getPB()
{
    return PORTBbits.RB12;
}