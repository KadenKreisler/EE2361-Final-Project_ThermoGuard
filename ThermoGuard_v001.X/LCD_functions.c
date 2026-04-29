#include <stdio.h>
#include <string.h>
#include "xc.h"

#define FCY 16000000UL
#include <libpic30.h>

#include "LCD_base_library.h"
#include "LCD_functions.h"

#define INFO     0
#define SETTEMP  1
#define SETTIME  2
#define ARM      3
#define DISSABLE 4
#define CONFIRM  5
#define ALARM    6

int state = INFO;
int page = 0;
int click = UNPRESSED;

extern int PIR;

int JoyStickValueX = 512, JoyStickValueY = 512;
int buttonState = 1;

int systemEnabled = 0;  

double currTemp = 25.0;
double maxTemp = 75.0;

int timerSet = 10;
int timeRemaining = 0;

double adjTemp = 0;
int adjTimer = 0;

int systemArmed = 0;
int confirmTarget = 0;

volatile unsigned long rollover = 0;
unsigned long lastStep = 0;
unsigned long lastSecond = 0;
unsigned long holdStart = 0;

//This function sets the servo arm to the alarm position
void servo_alarm(void)
{
    setServo(4000);
}

//This function sets the servo arm to the "normal" or general operating position
void servo_reset(void)
{
    setServo(3000);
}

//This interrupt is used to keep track of the total time for timer one using a rollover bit.
void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void)
{
    rollover++;
    IFS0bits.T1IF = 0;
}

//This function initializes the setup for timer 1
void init_tmr1(void)
{
    T1CON = 0;              // clear config
    T1CONbits.TCKPS = 0b01; // 1:8 prescaler

    TMR1 = 0;
    PR1 = 2000;             // sets interrupt rate

    IPC0bits.T1IP = 2;      // priority
    IFS0bits.T1IF = 0;      // clear flag
    IEC0bits.T1IE = 1;      // enable interrupt

    T1CONbits.TON = 1;      // start timer
}

//This function updates all the local variables used across the general functioning of the LCD
//including de-bouncing the joystick PB
void LCD_updateInputs(int x, int y, int button,int pir, double tempF)
{
    JoyStickValueX = x;
    JoyStickValueY = y;
    currTemp = tempF;
    buttonState = button;
    PIR = pir;

    static int prevButton = 1;
    static int initialized = 0;
    static unsigned long lastClickTime = 0;

    if(!initialized)
    {
        prevButton = button;
        initialized = 1;
        return;
    }

    int xNeutral = (x > 450 && x < 550);
    int yNeutral = (y > 450 && y < 550);

    if(!xNeutral || !yNeutral)
    {
        prevButton = button;
        return;
    }

    if(button == 0 && prevButton == 1)
    {
        if(rollover - lastClickTime > 200)
        {
            click = 1;
            lastClickTime = rollover;
        }
    }

    prevButton = button;
}

//This is the main function to run the entirety of the ThermoGaurd software
//It contains a state machine and combines all of our inputs to update and interact
//With the LCD and the different screens we choose to show on it.
void LCD_function_main(void)
{
    static int lastX = 512;

    if(state != CONFIRM && state != ALARM)
    {
        if(JoyStickValueX > 600 && lastX <= 600)
        {
            page++;
            click = 0;
            lastStep = rollover;
            clear_screen();
        }

        if(JoyStickValueX < 400 && lastX >= 400)
        {
            page--;
            click = 0;
            lastStep = rollover;
            clear_screen();
        }

        if(page > 4)
        {
            page = 0;
        }
        
        if(page < 0)
        {
            page = 4;
        }
        
        state = page;
    }

    if(rollover - lastStep < 200)
    {
        click = 0;
    }
    
    lastX = JoyStickValueX;

    if(systemArmed && systemEnabled)
    {
        static int prevPIR = 0;

        if(PIR == 1 && prevPIR == 0)
        {
            timeRemaining = timerSet * 60;
        }
        
        prevPIR = PIR;

        if(rollover - lastSecond > 1000)
        {
            lastSecond = rollover;
            if(timeRemaining > 0)
            {
                timeRemaining--;
            }
        }
    }

    if(systemArmed && systemEnabled)
    {
        if(timeRemaining == 0 && currTemp > maxTemp)
        {
            systemArmed = 0;
            servo_alarm();
            state = ALARM;
            clear_screen();
        }
    }

    switch(state)
    {
        case INFO:
            info_state();
            break;
            
        case SETTEMP:
            settemp_state();
            break;
            
        case SETTIME:
            settimer_state();
            break;
            
        case ARM:
            arm_state();
            break;
            
        case DISSABLE:
            Dissable_state();
            break;
            
        case CONFIRM:
            confirm_state();
            break;
            
        case ALARM:
            alarm_state();
            break;
    }
}

//This function is the screen/state where the user disables the device
void Dissable_state(void)
{
    char l0[21], l1[21], l2[21], l3[21];

    snprintf(l0,21,"%-20s","SYSTEM CTRL");
    snprintf(l1,21,"%-20s"," Turn OFF");
    snprintf(l2,21,"%-20s","Press: Btn");
    snprintf(l3,11,"%10s","<Pg>");

    print(l0,l1,l2,l3);

    if(click)
    {
        click = 0;
        systemEnabled = 0;
        systemArmed = 0;
        timeRemaining = timerSet * 60;   //RESET TIMER
        servo_reset();
        clear_screen();
       
        state = INFO;
        page = INFO;
    }
}

//This function is the main state for the general running of our device
//It displays all the information and allows the user to traverse to other screens
void info_state(void)
{
    char l0[21], l1[21], l2[21], l3[21];

    int m = timeRemaining / 60;
    int s = timeRemaining % 60;

    snprintf(l0,21,"%-20s","SYSTEM RUN");
    snprintf(l1,21,"Temp:%4.1fF", currTemp);
    snprintf(l2,21,"Max :%4.1fF", maxTemp);

    char temp[20];
    snprintf(temp,20,"%2d:%02d <Pg>", m, s);
    snprintf(l3,21,"%-20s",temp);

    print(l0,l1,l2,l3);
}

//This function is used to set the temperature setpoint
//it pushes a display, and follows the joystick y axis to determine the increase
//or decrease of the temperature set
void settemp_state(void)
{
    char l0[21], l1[21], l2[21], l3[21];

    if(rollover - lastStep > 120)
    {
        if(JoyStickValueY > 600)
        {
            adjTemp++;
        }
        
        if(JoyStickValueY < 400)
        {
            adjTemp--;
        }
        
        lastStep = rollover;
    }

    snprintf(l0,21,"%-20s","MAX TEMP");

    char temp[20];
    snprintf(temp,20,"Val:%4.1f F", adjTemp);
    snprintf(l1,21,"%-20s",temp);

    snprintf(l2,21,"%-20s","^ v Adjust");
    snprintf(l3,21,"%-20s","Press=Save");

    print(l0,l1,l2,l3);

    if(click)
    {
        click = 0;
        confirmTarget = 1;
        clear_screen();
        state = CONFIRM;
    }
}

//This function is used to set the timer length
//it pushes a display, and follows the joystick y axis to determine the increase
//or decrease of the timer set
void settimer_state(void)
{
    char l0[21], l1[21], l2[21], l3[21];

    if(rollover - lastStep > 120)
    {
        if(JoyStickValueY > 600)
        {
            adjTimer++;
        }
        
        if(JoyStickValueY < 400 && adjTimer>0) 
        {
            adjTimer--;
        }
        
        lastStep = rollover;
    }

    snprintf(l0,21,"%-20s","SET TIMER");

    char temp[20];
    snprintf(temp,20,"Val:%2d min", adjTimer);
    snprintf(l1,21,"%-20s",temp);

    snprintf(l2,21,"%-20s","^ v Adjust");
    snprintf(l3,21,"%-20s","Press=Save");

    print(l0,l1,l2,l3);

    if(click)
    {
        click = 0;
        confirmTarget = 2;
        clear_screen();
        state = CONFIRM;
    }
}

//This function arms the device
//Displays an output message and when the user chooses to move forward
//The device is rearmed and set to run
void arm_state(void)
{
    char l0[21], l1[21], l2[21], l3[21];

    snprintf(l0,21,"%-20s","READY");

    char t1[20];
    snprintf(t1,20,"Temp:%4.1fF", maxTemp);
    snprintf(l1,21,"%-20s",t1);

    char t2[20];
    snprintf(t2,20,"Time:%2dmin", timerSet);
    snprintf(l2,21,"%-20s",t2);

    snprintf(l3,21,"%-20s","Press: Btn");

    print(l0,l1,l2,l3);

    if(click)
    {
        click = 0;
        systemEnabled = 1;
        systemArmed = 1;
        timeRemaining = timerSet * 60;
        clear_screen();
        state = INFO;
        page = 0;
    }
}

//This function is the interaction to confirm a user choice.
//Pushes a message and follows movement to determine a user choice and allow them
//to pick the outcome
void confirm_state(void)
{
    char l0[21], l1[21], l2[21], l3[21];
    static int sel = 0;

    if(JoyStickValueX < 400)
    {
        sel = 0;
    }
    
    if(JoyStickValueX > 600)
    {
        sel = 1;
    }
    
    snprintf(l0,21,"%-20s","CONFIRM");

    if(confirmTarget == 1)
    {
        snprintf(l1,21,"%-20s","Set Temp?");
    }
    else
    {
        snprintf(l1,21,"%-20s","Set Time?");
    }
    
    char temp[20];
    if(confirmTarget == 1)
    {
        snprintf(temp,20,"Val:%4.1f F", adjTemp);
    }
    else
    {
        snprintf(temp,20,"Val:%2d min", adjTimer);
    }
    
    snprintf(l2,21,"%-20s",temp);

    if(sel == 0)
    {
        snprintf(l3,21,"%-20s",">YES   NO");
    }
    else
    {
        snprintf(l3,21,"%-20s"," YES  >NO");
    }
    
    print(l0,l1,l2,l3);

    if(click)
    {
        click = 0;

        if(sel == 0)
        {
            if(confirmTarget == 1)
            {
                maxTemp = adjTemp;
            }
            
            if(confirmTarget == 2)
            {
                timerSet = adjTimer;
            }
        }

        clear_screen();
        state = ARM;
        page = ARM;
    }
}

//This function holds the interactions for the device in the alarm state
//pushing an alarm message, and locking the servo while waiting for the user to
//reset the device
void alarm_state(void)
{
    char l0[21], l1[21], l2[21], l3[21];

    snprintf(l0,21,"%-20s","!!! ALARM !!!");
    snprintf(l1,21,"%-20s","Unattended");
    snprintf(l2,21,"%-20s","Hold Btn");
    snprintf(l3,21,"%-20s","3s to Reset");

    print(l0,l1,l2,l3);

    if(buttonState == 0)
    {
        if(holdStart == 0)
        {
            holdStart = rollover;
        }
        
        if(rollover - holdStart > 3000)
        {
            holdStart = 0;
            servo_reset();
            clear_screen();
            state = INFO;
        }
    }
    else
    {
        holdStart = 0;
    }
}

//This function prints a string for each row on the LCD
void print(char* s0,char* s1,char* s2,char* s3)
{
    char* d[4] = {s0,s1,s2,s3};

    for(int r = 0; r < 4; r++)
    {
        lcd_setCursor4rows(0,r);
        for(int i = 0; i < 20; i++)
        {
            if(d[r][i])
            {
                lcd_printChar(d[r][i]);
            }
            else
            {
                lcd_printChar(' ');
            }
        }
    }
}

//This function clears the screen by printing a blank to each row.
void clear_screen(void)
{
    print("","","","");
}