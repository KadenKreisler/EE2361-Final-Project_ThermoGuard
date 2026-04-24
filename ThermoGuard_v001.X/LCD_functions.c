#include <string.h>
#include <stdio.h> // Needed for sprintf
#include "xc.h"    // Needed for SFR definitions

#define FCY 16000000UL
#include <libpic30.h>
#include "LCD_base_library.h"
#include "LCD_functions.h"


int JoyStickValueX = 512, JoyStickValueY = 512;
int JoyStickClick = 3;
double currTemp = 25.0, currTimer = 0.0;
int timetoalarm = 100;
int state = 1;


#define DEFAULT 1
#define SETTEMP 2
#define SETTIME 3
#define CONFIRM 4
#define ALARM 5
#define RESET 0
#define UNPRESSED 6
#define PRESSED 7


double adjTemp = 0; 
double adjTimer = 0;
int click = UNPRESSED;


volatile unsigned long rollover = 0;
unsigned long timer_1_last = 0;

char adStr0[20];
char adStr1[20];
char adStr2[20];
char adStr3[20];


void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void) {
    rollover++;
    IFS0bits.T1IF = 0;
}

void init_tmr1 (void){ 
    T1CONbits.TON = 0;
    T1CONbits.TCS = 0;
    T1CONbits.TCKPS = 0b01;
    TMR1 = 0;
    PR1 = 2000;
    IPC0bits.T1IP = 2;
    IFS0bits.T1IF = 0;
    IEC0bits.T1IE = 1;
    T1CONbits.TON = 1;

} 

void LCD_function_main(void) {
    
    if (JoyStickValueX > 600) {
        if (rollover - timer_1_last > 200) {
            adjTemp += 1.0; 
            timer_1_last = rollover;
        }
        state = SETTEMP;
    }
    
    if (JoyStickValueX < 400) {
        if (rollover - timer_1_last > 200) {
            adjTemp -= 1.0;
            timer_1_last = rollover;
        }
        state = SETTEMP;
    }

  
    if (JoyStickValueY > 600) {
        if (rollover - timer_1_last > 200) {
            adjTimer += 1;
            timer_1_last = rollover;
        }
        state = SETTIME;
    }
    
    if (timetoalarm == 0){ 
        
        state = ALARM;
    } 
}



void default_state(void) {
       __delay_ms(35);
    sprintf(adStr0, "Temp: %6.2f C", currTemp);
    sprintf(adStr1, "Timer: %d m", (int)currTimer);
    sprintf(adStr2, "Temp Set ->");
    sprintf(adStr3, "<- Timer Set");
    print(adStr0, adStr1, adStr2, adStr3);
}

void settemp_state(void) {
       __delay_ms(35);
    sprintf(adStr0, "Adjust Temp:");
    sprintf(adStr1, "Set: %6.2f C", adjTemp);
    sprintf(adStr2, " ");
    sprintf(adStr3, "Click to save");
    print(adStr0, adStr1, adStr2, adStr3);
    
    if (click == PRESSED) {
        state = CONFIRM;
        click = UNPRESSED; // Reset click
    }
}

void settimer_state (void){ 
    __delay_ms(35); 
        sprintf(adStr0, "Temp setpoint:", adjTimer);  // ?x.xxxx Celsius
        sprintf (adStr1, "Set: %6.4f C", adjTimer); 
        sprintf (adStr2, " "); 
        sprintf (adStr3, " "); 
        
        print (adStr0, adStr1, adStr2, adStr3); 
        while (click == UNPRESSED); 
        state = CONFIRM; 
        
}

void confirmation_state (void){ 
    __delay_ms(35); 
      sprintf(adStr0, "Are you sure?");  // ?x.xxxx Celsius
        sprintf (adStr1, " "); 
        sprintf (adStr2, "No ->"); 
        sprintf (adStr3, "<- Yes"); 
        
        print (adStr0, adStr1, adStr2, adStr3);
        click = UNPRESSED; 
        state = DEFAULT; 
        
}

void alarm_state (void){ 
    __delay_ms(35); 
     sprintf(adStr0, "Thresholds");  // ?x.xxxx Celsius
        sprintf (adStr1, "Exceeded"); 
        sprintf (adStr2, "Device"); 
        sprintf (adStr3, "Disabled"); 
        
        print (adStr0, adStr1, adStr2, adStr3); 
        
        __delay_ms (20000); 
        state = RESET; 
        
}

void reset_state (void){ 
    __delay_ms(35); 
     sprintf(adStr0, "Hold down button");  // ?x.xxxx Celsius
        sprintf (adStr1, " to reset"); 
        sprintf (adStr2, "   "); 
        sprintf (adStr3, "   "); 
        
        print (adStr0, adStr1, adStr2, adStr3); 
        while (click != PRESSED); 
        click = UNPRESSED; 
        state = DEFAULT; 
}


void print(char* s0, char* s1, char* s2, char* s3) {
    int i;
    char* data[4] = {s0, s1, s2, s3};
    
    for (int row = 0; row < 4; row++) {
        lcd_setCursor4rows(0, row);
        for (i = 0; i < 20; i++) {
            if (data[row][i] == '\0'){ 
                break;
            } 
            lcd_printChar(data[row][i]);
        }
    }
}



   
        
