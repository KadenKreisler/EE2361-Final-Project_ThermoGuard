/*
 * File:   ThermoGaurd_PIR_v001.c
 * Author: Kaden
 *
 * Created on April 14, 2026, 11:03 PM
 */


#include "xc.h"
#include "ThermoGaurd_PIR_v001.h"

void PIR_init()
{    
    AD1PCFG |= 0b0000000000100000; //Sets pin 5 digital
    TRISB |= 0b0000000000100000;   // Set pin 5 as input
}

int PIR_GetData()
{
    return PORTBbits.RB5;
}
//Potentially an interupt for the data resetting the timeout timer?