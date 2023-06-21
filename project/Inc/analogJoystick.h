/*
 * analogJoystick.h
 *
 *  Created on: 15. jun. 2023
 *      Author: sofus
 */

#ifndef ANALOGJOYSTICK_H_
#define ANALOGJOYSTICK_H_

void setPinPA6();
void setPinPA7();
void setPinF1();
void setPinB5();
void initPins();
void configureADC();
int16_t measurePA6();
int16_t measurePA7();
int16_t getPF1();
int16_t getPB5();


#endif /* ANALOGJOYSTICK_H_ */
