
#include "TempSen.h"

#include "xc.h"
#include <stdint.h>

#define FCY 16000000UL
#include <libpic30.h>


int detection = 0;
double var = 0;
uint8_t temp_data[9];   // fixed type (was char)


typedef enum {
    TEMP_IDLE,
    TEMP_START,
    TEMP_WAIT,
    TEMP_READ
} temp_state_t;

static temp_state_t temp_state;
static int temp_ready_flag;

void low()
{
    LATBbits.LATB13 = 0;
    TRISBbits.TRISB13 = 0;
}

void release()
{
    TRISBbits.TRISB13 = 1;   // external pull-up required
}

int temp_reset(void)
{
    detection = 0;

    low();
    __delay_us(480);

    release();
    __delay_us(80);

    if(PORTBbits.RB13 == 0)
        detection = 1;

    __delay_us(400);

    return detection;
}

void write_0()
{
    low();
    __delay_us(60);
    release();
    __delay_us(5);
}

void write_1()
{
    low();
    __delay_us(5);
    release();
    __delay_us(55);
}

int read_bit()
{
    int value = 0;

    low();
    __delay_us(3);

    release();
    __delay_us(10);

    if(PORTBbits.RB13 == 1)
        value = 1;

    __delay_us(50);

    return value;
}

int read_byte()
{
    int byte_2 = 0;

    for(int i = 0; i < 8; i++)
    {
        if(read_bit())
            byte_2 |= (1 << i);
    }

    return byte_2;
}

void write_byte(char byte_1)
{
    for(int i = 0; i < 8; i++)
    {
        if(byte_1 & 0x01)
            write_1();
        else
            write_0();

        byte_1 >>= 1;
    }
}

void temp_init(void)
{
    temp_state = TEMP_IDLE;
    temp_ready_flag = 0;
    var = 0;
}

void temp_update(void)
{
    switch(temp_state)
    {
        case TEMP_IDLE:
            temp_state = TEMP_START;
            break;

        case TEMP_START:
            if(!temp_reset()) return;

            write_byte(0xCC);   // skip ROM
            write_byte(0x44);   // start conversion

            temp_state = TEMP_WAIT;
            break;

        case TEMP_WAIT:
        
            if(read_bit())   
            {
                temp_state = TEMP_READ;
            }
            break;

        case TEMP_READ:
            if(!temp_reset()) return;

            write_byte(0xCC);
            write_byte(0xBE);

            for(int i = 0; i < 9; i++)
                temp_data[i] = read_byte();

            uint16_t lsByte = temp_data[0];
            uint16_t msByte = temp_data[1];

            int16_t tempWord = (msByte << 8) | lsByte;

            var = tempWord / 16.0;

            temp_ready_flag = 1;
            temp_state = TEMP_IDLE;
            break;
    }
}

double get_TempC(void)
{
    return var;
}

int temp_ready(void)
{
    return temp_ready_flag;
}