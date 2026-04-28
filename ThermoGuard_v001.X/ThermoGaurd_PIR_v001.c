/*
 * File:   ThermoGaurd_PIR_v001.c
 * Author: Kaden
 *
 * Created on April 14, 2026, 11:03 PM
 */


#include "xc.h"
#include "ThermoGaurd_PIR_v001.h"

//This function initializes the pin used for the PIR motion sensor
void PIR_init()
{    
    AD1PCFG |= 0b0000000000100000; //Sets pin 5 digital
    TRISB |= 0b0000000000100000;   // Set pin 5 as input
}

//This function returns the state of the PIR sensor, 1 means something detected, 0 means nothing
int PIR_GetData()
{
    return PORTBbits.RB5;
}
