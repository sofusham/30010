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
void initPins();
void configureADC();
int16_t measureA6();
int16_t measureA7();


#endif /* ANALOGJOYSTICK_H_ */
