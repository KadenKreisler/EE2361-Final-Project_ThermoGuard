/* 
 * File:   ThermoGaurd_Joystick_v001.h
 * Author: Kaden
 *
 * Created on April 15, 2026, 1:46 AM
 */

#ifndef THERMOGAURD_JOYSTICK_V001_H
#define	THERMOGAURD_JOYSTICK_V001_H

#ifdef	__cplusplus
extern "C" {
#endif
    void Joystick_init();
    int joystick_getX();
    int joystick_getY();
    int joystick_getPB();


#ifdef	__cplusplus
}
#endif

#endif	/* THERMOGAURD_JOYSTICK_V001_H */

