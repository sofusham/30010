#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "stdio.h"
#include "stdint.h"
#include "timer.h"
#include "string.h"
#include "ansi.h"
#include "lcd.h"

volatile int centisecond = 0;

void TIM1_BRK_TIM15_IRQHandler(void) {
	centisecond++;
	TIM15 -> SR &= ~0x0001;
}


void configureTimer() {
	RCC -> APB2ENR |= RCC_APB2Periph_TIM15;
	TIM15 -> CR1 = 0x000;
	TIM15 -> ARR = 0x9C3;
	TIM15 -> PSC = 0x0FF;
	TIM15 -> CR1 = 0x001;
	TIM15 -> DIER |= 0x0001;

	NVIC_SetPriority(TIM1_BRK_TIM15_IRQn, 0);
	NVIC_EnableIRQ(TIM1_BRK_TIM15_IRQn);
}

uint8_t* read_uart_data(uint8_t num_chars) {
	static uint8_t data[10];
	for (uint8_t i = 0; i < num_chars; i++) {
		while(1) {
			uint8_t input = uart_get_char();
			if (input != 0) {
				if(input != 0x0D){
					data[i] = input;
					break;
				} else {
					data[i] = 0;
					i = num_chars;
					break;
				}
			}
		}
	}
	data[num_chars] = 0x00;
	return data;
}

uint8_t string_check(char * data) {
	//Checks if input is "Enter"
	if( !(strcmp(data, "\0x0D"))) {return 1;}
	else {return 0;}
}

