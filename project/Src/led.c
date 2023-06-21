/*
 * led.c
 *
 *  Created on: 21. jun. 2023
 *      Author: sofus
 */
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "led.h"

void setLED(uint32_t lives) {
	if (lives == 3 || lives == 2) {
		GPIOB -> ODR &= ~(0x01 << 4);
		GPIOC -> ODR &= ~(0x01 << 7);
		GPIOA -> ODR &= ~(0x01 << 9);
		GPIOA -> ODR |= (0x0001 << 9);
		GPIOB -> ODR |= (0x0001 << 4);
		GPIOC -> ODR |= ~(0x0001 << 7);
	}
	else if (lives) {
		GPIOB -> ODR &= ~(0x01 << 4);
		GPIOC -> ODR &= ~(0x01 << 7);
		GPIOA -> ODR &= ~(0x01 << 9);
		GPIOB -> ODR |= ~(0x0001 << 4);
		GPIOC -> ODR |= ~(0x0001 << 7);
		GPIOA -> ODR |= (0x0001 << 9);
	}
	else if (lives == 0) {
		GPIOB -> ODR &= ~(0x01 << 4);
		GPIOC -> ODR &= ~(0x01 << 7);
		GPIOA -> ODR &= ~(0x01 << 9);
		GPIOA -> ODR |= (0x0001 << 9);
		GPIOC -> ODR |= (0x0001 << 7);
		GPIOB -> ODR |= ~(0x0001 << 4);
	}
	/*else if (readJoystick() == 0x07) {
		GPIOC -> ODR = (0x0001 << 7);
		GPIOA -> ODR = ~(0x0001 << 9);
		GPIOB -> ODR = ~(0x0001 << 4);
	}
	else if (readJoystick() == 0x10) {
		GPIOA -> ODR = (0x0001 << 9);
		GPIOC -> ODR = ~(0x0001 << 7);
		GPIOB -> ODR = ~(0x0001 << 4);
	}
	else {
		GPIOA -> ODR = ~(0x0001 << 9);
		GPIOC -> ODR = ~(0x0001 << 7);
		GPIOB -> ODR = ~(0x0001 << 4);
	}*/
}

void setPinPA9() {
	GPIOA -> OSPEEDR &= ~(0x00000003 << (9 * 2));
	GPIOA -> OSPEEDR |= ~(0x00000002 << (9 * 2));
	GPIOA -> OTYPER &= ~(0x001 << (9));
	GPIOA -> OTYPER |= (0x000 << (9));
	GPIOA -> MODER &= ~(0x00000003 << (9 * 2));
	GPIOA -> MODER |= (0x00000001 << (9 * 2));
}

void setPinPC7() {
	GPIOC -> OSPEEDR &= ~(0x00000003 << (7 * 2));
	GPIOC -> OSPEEDR |= ~(0x00000002 << (7 * 2));
	GPIOC -> OTYPER &= ~(0x001 << (7));
	GPIOC -> OTYPER |= (0x000 << (7));
	GPIOC -> MODER &= ~(0x00000003 << (7 * 2));
	GPIOC -> MODER |= (0x00000001 << (7 * 2));
}

void setPinPB4() {
	GPIOB -> OSPEEDR &= ~(0x00000003 << (4 * 2));
	GPIOB -> OSPEEDR |= ~(0x00000002 << (4 * 2));
	GPIOB -> OTYPER &= ~(0x001 << (4));
	GPIOB -> OTYPER |= (0x000 << (4));
	GPIOB -> MODER &= ~(0x00000003 << (4 * 2));
	GPIOB -> MODER |= (0x00000001 << (4 * 2));
}

void initLED() {
	RCC -> AHBENR |= RCC_AHBPeriph_GPIOA;
	RCC -> AHBENR |= RCC_AHBPeriph_GPIOB;
	RCC -> AHBENR |= RCC_AHBPeriph_GPIOC;
	setPinPA9();
	setPinPC7();
	setPinPB4();
}


