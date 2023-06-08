#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "joystick.h"


void setPinPA4() {
	GPIOA -> MODER &= ~(0x00000003 << (4 * 2));
	GPIOA -> MODER |= (0x00000000 << (4 * 2));

	GPIOA -> PUPDR &= ~(0x00000003 << (4 * 2));
	GPIOA -> PUPDR |= (0x00000002 << (4 * 2));
}

void setPinPC0() {
	GPIOC -> MODER &= ~(0x00000003 << (0 * 2));
	GPIOC -> MODER |= (0x00000000 << (0 * 2));

	GPIOC -> PUPDR &= ~(0x00000003 << (0 * 2));
	GPIOC -> PUPDR |= (0x00000002 << (0 * 2));
}

void setPinPB5() {
	GPIOB -> MODER &= ~(0x00000003 << (5 * 2));
	GPIOB -> MODER |= (0x00000000 << (5 * 2));

	GPIOB -> PUPDR &= ~(0x00000003 << (5 * 2));
	GPIOB -> PUPDR |= (0x00000002 << (5 * 2));
}

void setPinPC1() {
	GPIOC -> MODER &= ~(0x00000003 << (1 * 2));
	GPIOC -> MODER |= (0x00000000 << (1 * 2));

	GPIOC -> PUPDR &= ~(0x00000003 << (1 * 2));
	GPIOC -> PUPDR |= (0x00000002 << (1 * 2));
}

void setPinPB0() {
	GPIOB -> MODER &= ~(0x00000003 << (0 * 2));
	GPIOB -> MODER |= (0x00000000 << (0 * 2));

	GPIOB -> PUPDR &= ~(0x00000003 << (0 * 2));
	GPIOB -> PUPDR |= (0x00000002 << (0 * 2));
}

void initPins() {
	RCC -> AHBENR |= RCC_AHBPeriph_GPIOA;
	RCC -> AHBENR |= RCC_AHBPeriph_GPIOB;
	RCC -> AHBENR |= RCC_AHBPeriph_GPIOC;
	setPinPA4();
	setPinPC0();
	setPinPB5();
	setPinPC1();
	setPinPB0();
}

int32_t readJoystick() {
	uint16_t up = GPIOA -> IDR & (0x0001 << 4);
	uint16_t right = GPIOC -> IDR & (0x0001 << 0);
	uint16_t center = GPIOB -> IDR & (0x0001 << 5);
	uint16_t left = GPIOC -> IDR & (0x0001 << 1);
	uint16_t down = GPIOB -> IDR & (0x0001 << 0);

	if (up) {return 0x01; }
	else if (down) {return 0x02;}
	else if (left) {return 0x04;}
	else if (right) {return 0x07;}
	else if (center) {return 0x10;}
	else {return 0x00;}
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

void initLed() {
	RCC -> AHBENR |= RCC_AHBPeriph_GPIOA;
	RCC -> AHBENR |= RCC_AHBPeriph_GPIOB;
	RCC -> AHBENR |= RCC_AHBPeriph_GPIOC;
	setPinPA9();
	setPinPC7();
	setPinPB4();
}

void setLed() {
	if (readJoystick() == 0x01) {
		GPIOA -> ODR = (0x0001 << 9);
		GPIOC -> ODR = (0x0001 << 7);
		GPIOB -> ODR = ~(0x0001 << 4);
	}
	else if (readJoystick() == 0x02) {
		GPIOB -> ODR = (0x0001 << 4);
		GPIOC -> ODR = (0x0001 << 7);
		GPIOA -> ODR = ~(0x0001 << 9);
	}
	else if (readJoystick() == 0x04) {
		GPIOA -> ODR = (0x0001 << 9);
		GPIOB -> ODR = (0x0001 << 4);
		GPIOC -> ODR = ~(0x0001 << 7);
	}
	else if (readJoystick() == 0x07) {
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
	}
}



