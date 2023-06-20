/*
 * timer2.h
 *
 *  Created on: 12. jun. 2023
 *      Author: sofus
 */

#ifndef TIMER2_H_
#define TIMER2_H_

extern volatile int timer2;

void configure_timer2();
void set_freq(uint16_t freq);
void stop_buzzer();

#endif /* TIMER2_H_ */
