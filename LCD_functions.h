
#ifndef LCD_FUNCTIONS_H
#define	LCD_FUNCTIONS_H


#include <string.h>
#include <stdio.h> // Needed for sprintf
#include "xc.h"    // Needed for SFR definitions

#define FCY 16000000UL
#include <libpic30.h>
#include "LCD_base_library.h"
#include "LCD_functions.h"

//Can be removed?
#define DEFAULT 1
#define SETTEMP 2
#define SETTIME 3
#define CONFIRM 4
#define ALARM 5
#define RESET 0
#define UNPRESSED 6
#define PRESSED 7

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    void init_tmr1(void);
    void LCD_updateInputs(int x, int y, int button,int pir, double tempF);
    void LCD_function_main(void);
    void Dissable_state(void);
    void info_state(void);
    void settemp_state(void);
    void settimer_state(void);
    void arm_state(void);
    void confirm_state(void);
    void alarm_state(void);
    void print(char* s0,char* s1,char* s2,char* s3);
    void clear_screen(void);
   
#endif
