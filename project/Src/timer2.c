/*
 * timer2.c
 *
 *  Created on: 12. jun. 2023
 *      Author: sofus
 */
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "timer2.h"

volatile int timer2 = 0;

void TIM1_BRK_TIM2_IRQHandler(void) {
	timer2++;
	TIM2 -> SR &= ~0x0001;
}

void configure_timer2() {
	RCC -> APB1ENR |= RCC_APB1Periph_TIM2;
	RCC -> AHBENR |= RCC_AHBPeriph_GPIOB;

	TIM2 -> CR1 = 0x000;
	TIM2 -> ARR = 63999;
	TIM2 -> PSC = 0;
	TIM2 -> CR1 = 0x001;
	TIM2 -> DIER |= 0x0001;

	NVIC_SetPriority(TIM1_BRK_TIM15_IRQn, 0);
	NVIC_EnableIRQ(TIM1_BRK_TIM15_IRQn);

	TIM2 -> CCER &= ~TIM_CCER_CC3P; // Clear CCER register
	TIM2->CCER |= 0x00000001 << 8; // Enable OC3 output

	TIM2->CCMR2 &= ~TIM_CCMR2_OC3M; // Clear CCMR2 register
	TIM2->CCMR2 &= ~TIM_CCMR2_CC3S;
	TIM2->CCMR2 |= TIM_OCMode_PWM1; // Set output mode to PWM1
	TIM2->CCMR2 &= ~TIM_CCMR2_OC3PE;
	TIM2->CCMR2 |= TIM_OCPreload_Enable;
	TIM2->CCR3 = 63999 / 2; // Set duty cycle to 50 %

	GPIOB -> MODER &= ~(0x00000003 << (10 * 2));
	GPIOB -> MODER |= (0x00000002 << (10 * 2));

	GPIOB -> PUPDR &= ~(0x00000003 << (10 * 2));
	GPIOB -> PUPDR |= (0x00000002 <<(10 * 2));

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_1);
}

void set_freq(uint16_t freq) {
	uint32_t reload = 64e6 / freq / (0 + 1) - 1;

	TIM2 -> ARR = reload;
	TIM2 -> CCR3 = reload / 2;

	TIM2 -> EGR |= 0x01;
}

void stop_buzzer() {
	TIM2 -> CCR3 = 0;
}

uint16_t read_flash(int16_t offset) {
	uint32_t baseAddress = 0x0800F800 + offset;
	uint16_t tempVal;
	for (int i = 0; i < 10; i++) {
		tempVal = *(uint16_t *) (baseAddress + i  * 2);
		printf("%d", tempVal);
	}
}

void write_flash(int16_t offset, int16_t data[]) {
	FLASH_Unlock();
	FLASH_ClearFlag( FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR );
	FLASH_ErasePage( 0x0800F800 + offset );
	FLASH_ProgramHalfWord(0x0800F800 + offset, data);
}
