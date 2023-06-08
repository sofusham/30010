/*
 * joystick.h
 *
 *  Created on: 6. jun. 2023
 *      Author: sofus
 */

#ifndef JOYSTICK_H_
#define JOYSTICK_H_

void setPinPA4();
void setPinPC0();
void setPinPB5();
void setPinPC1();
void setPinPB0();
void initPins();
int32_t readJoystick();
void setPinPA9();
void setPinPC7();
void setPinPB4();
void initLed();
void setLed();

#endif /* JOYSTICK_H_ */

