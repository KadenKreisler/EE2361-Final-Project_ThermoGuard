#include "TempSen.h"
#include "xc.h"
#include <stdint.h>

#define FCY 16000000UL
#include <libpic30.h>

int detection = 0;
double var = 0;
uint8_t temp_data[9];

typedef enum {
    TEMP_IDLE,
    TEMP_START,
    TEMP_WAIT,
    TEMP_READ
} temp_state_t;

static temp_state_t temp_state;
static unsigned long temp_timer;
static int temp_ready_flag;

extern volatile unsigned long rollover;

//This function sets the pin to a output sending a low signal
void low()
{
    LATBbits.LATB13 = 0;
    TRISBbits.TRISB13 = 0;
}

//This function sets the pin to an input "releasing" the output
void release()
{
    TRISBbits.TRISB13 = 1;
}

//This function resets the temp sensor, and returns if it resets successfully 
int temp_reset(void)
{
    __builtin_disi(0x3FFF);   // disable interrupts

    detection = 0;

    low();
    __delay_us(480);

    release();
    __delay_us(80);

    if(PORTBbits.RB13 == 0)
    {
        detection = 1;
    }

    __delay_us(400);

    __builtin_disi(0x0000);   // enable interrupts

    return detection;
}

//This function writes a zero through the one-wire protocol
void write_0()
{
    __builtin_disi(0x3FFF);

    low();
    __delay_us(60);
    release();
    __delay_us(5);

    __builtin_disi(0x0000);
}

//This function writes a 1 through the one-wire protocol
void write_1()
{
    __builtin_disi(0x3FFF);

    low();
    __delay_us(5);
    release();
    __delay_us(55);

    __builtin_disi(0x0000);
}

//This function sends 1 byte through the one wire protocol, or 8 bits in a row
void write_byte(char byte_1)
{
    for(int i = 0; i < 8; i++)
    {
        if(byte_1 & 0x01)
        {
            write_1();
        }
        else
        {
            write_0();
        }

        byte_1 >>= 1;
    }
}

//This function reads the bit given by the temp sensor
int read_bit()
{
    int value;

    __builtin_disi(0x3FFF);

    low();
    __delay_us(3);

    release();
    __delay_us(10);

    value = PORTBbits.RB13;

    __delay_us(50);

    __builtin_disi(0x0000);

    return value;
}

//This function reads a byte from the temp sensor, by calling read bit 8 times.
int read_byte()
{
    int byte_2 = 0;

    for(int i = 0; i < 8; i++)
    {
        if(read_bit())
        {
            byte_2 |= (1 << i);
        }
    }

    return byte_2;
}

//This function initializes the state machine and pin used by the temp sensor
void temp_init(void)
{
    temp_state = TEMP_IDLE;
    temp_ready_flag = 0;
    
    LATBbits.LATB13 = 0;
    TRISBbits.TRISB13 = 1;
}

//This function determines what the temperature sensor does based off the state
//and depending on the state sends different instructions to the sensor
void temp_update(void)
{
    switch(temp_state)
    {
        case TEMP_IDLE:
            temp_state = TEMP_START;
            break;

        case TEMP_START:
            if(!temp_reset())
            {
                return;
            }

            write_byte(0xCC);
            write_byte(0x44);   // start conversion

            temp_timer = rollover;
            temp_state = TEMP_WAIT;
            break;

        case TEMP_WAIT:
            // wait 750ms using Timer1
            if(rollover - temp_timer >= 750)
            {
                temp_state = TEMP_READ;
            }
            break;

        case TEMP_READ:
            if(!temp_reset())
            {
                return;
            }

            write_byte(0xCC);
            write_byte(0xBE);

            for(int i = 0; i < 9; i++)
            {
                temp_data[i] = read_byte();
            }
            
            uint16_t lsByte = temp_data[0];
            uint16_t msByte = temp_data[1];

            int16_t tempWord = (msByte << 8) | lsByte;

            var = tempWord / 16.0;

            temp_ready_flag = 1;
            temp_state = TEMP_IDLE;
            break;
    }
}

//This function returns the temperature read in Celsius
double get_TempC(void)
{
    return var;
}

//This function returns a 1 if the temperature is done converting, or a 0 otherwise.
int temp_ready(void)
{
    return temp_ready_flag;
}