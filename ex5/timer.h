/*
 * timer.h
 *
 *  Created on: 7. jun. 2023
 *      Author: sofus
 */

#ifndef TIMER_H_
#define TIMER_H_

extern volatile centisecond;

void configureTimer();
void TIM1_BRK_TIM15_IRQHandler(void);


#endif /* TIMER_H_ */
