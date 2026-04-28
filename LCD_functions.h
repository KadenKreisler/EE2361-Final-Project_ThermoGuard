#ifndef LCD_FUNCTIONS_H
#define LCD_FUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

// ================= STATE DEFINITIONS =================
#define DEFAULT   1
#define SETTEMP   2
#define SETTIME   3
#define CONFIRM   4
#define ALARM     5
#define RESET     0

#define UNPRESSED 6
#define PRESSED   7

// ================= FUNCTIONS =================
void init_tmr1(void);

void LCD_updateInputs(int x, int y, int button,int pir, double temp);
void LCD_function_main(void);

void default_state(void);
void settemp_state(void);
void settimer_state(void);
void confirmation_state(void);
void alarm_state(void);
void reset_state(void);

void print(char* s0, char* s1, char* s2, char* s3);

#ifdef __cplusplus
}
#endif

#endif