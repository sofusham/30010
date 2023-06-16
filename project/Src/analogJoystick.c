/*
 * analogJoystick.c
 *
 *  Created on: 15. jun. 2023
 *      Author: sofus
 */
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course

//PA_13 og PA_14 til joystick
//PC_13 til knappen

int32_t button() {
	uint16_t up = GPIOB -> IDR & (0x0001 << 7);
	if (up) {return 1;}
}

void setPinPA13() {
	GPIOA -> MODER &= ~(0x00000001 << (13 * 2));
	GPIOA -> MODER |= (0x00000000 << (13 * 2));

	GPIOA -> PUPDR &= ~(0x00000003 << (13 * 2));
	GPIOA -> PUPDR |= (0x00000002 << (13 * 2));
}

void setPinPA14() {
	GPIOA -> MODER &= ~(0x00000001 << (14 * 2));
	GPIOA -> MODER |= (0x00000000 << (14 * 2));

	GPIOA -> PUPDR &= ~(0x00000003 << (14 * 2));
	GPIOA -> PUPDR |= (0x00000002 << (14 * 2));
}

void setPinPB7() {
	GPIOB -> MODER &= ~(0x00000003 << (7 * 2));
	GPIOB -> MODER |= (0x0000000 << (7 * 0));

	GPIOB -> PUPDR &= ~(0x00000003 << (7 * 2));
	GPIOB -> PUPDR |= (0x00000002 << (7 * 2));
}


void initPins() {
	RCC -> AHBENR |= RCC_AHBPeriph_GPIOA;
	RCC -> AHBENR |= RCC_AHBPeriph_GPIOB;
	//setPinPA13();
	//setPinPA14();
	setPinPB7();
}

