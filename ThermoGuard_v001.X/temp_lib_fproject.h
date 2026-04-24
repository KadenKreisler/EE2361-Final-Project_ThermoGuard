/* 
 * File:   temp_lib_fproject.h
 * Author: Kaden
 *
 * Created on April 24, 2026, 10:43 AM
 */

#ifndef TEMP_LIB_FPROJECT_H
#define	TEMP_LIB_FPROJECT_H

#ifdef	__cplusplus
extern "C" {
#endif

void low();
void release();
int temp_reset(void);
void write_0();
void write_1();
int read_bit();
int read_byte();
void write_byte(char byte_1);
int init_Temp();



#ifdef	__cplusplus
}
#endif

#endif	/* TEMP_LIB_FPROJECT_H */

