/*
 * timer.h
 *
 *  Created on: 7. jun. 2023
 *      Author: sofus
 */

#ifndef TIMER_H_
#define TIMER_H_

extern volatile int centisecond;

void configureTimer();
void TIM1_BRK_TIM15_IRQHandler(void);
uint8_t* read_uart_data(uint8_t num_chars);
uint8_t string_check(char * data);
void window(int x2, int y2, int x1, int y1);

#endif /* TIMER_H_ */
