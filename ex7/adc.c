/*
 * adc.c
 *
 *  Created on: 11. jun. 2023
 *      Author: sofus
 */
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "adc.h"

void configureADC()  {
	RCC -> CFGR2 &= ~RCC_CFGR2_ADCPRE12; // Clear ADC12 prescaler bits
	RCC -> CFGR2 |= RCC_CFGR2_ADCPRE12_DIV6; // Set ADC12 prescaler to 6
	RCC -> AHBENR |= RCC_AHBPeriph_ADC12; // Enable clock for ADC12

	ADC1 -> CR = 0x00000000; // Clear CR register
	ADC1 -> CFGR &= 0xFDFFC007; // Clear ADC1 config register
	ADC1 -> SQR1 &= ~ADC_SQR1_L; // Clear regular sequence register 1

	ADC2 -> CR = 0x00000000; // Clear CR register
	ADC2 -> CFGR &= 0xFDFFC007; // Clear ADC2 config register
	ADC2 -> SQR1 &= ~ADC_SQR1_L; // Clear regular sequence register 2
}

int16_t measurePA0() {
	ADC1->CR |= 0x10000000; // Enable internal ADC voltage regulator
	for (int i = 0 ; i < 1000 ; i++) {} // Wait for about 16 microseconds

	ADC1->CR |= 0x80000000; // Start ADC1 calibration
	while (!(ADC1->CR & 0x80000000)); // Wait for calibration to finish
	for (int i = 0 ; i < 100 ; i++) {} // Wait for a little while

	ADC1->CR |= 0x00000001; // Enable ADC1 (0x01 - Enable, 0x02 - Disable)
	while (!(ADC1->ISR & 0x00000001)); // Wait until ready

	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_1Cycles5);

	ADC_StartConversion(ADC1); // Start ADC read
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == 0); // Wait for ADC read

	uint16_t x = ADC_GetConversionValue(ADC1);
	return x;
}

int16_t measurePA1() {
	ADC1->CR |= 0x10000000; // Enable internal ADC voltage regulator
	for (int i = 0 ; i < 1000 ; i++) {} // Wait for about 16 microseconds

	ADC1->CR |= 0x80000000; // Start ADC1 calibration
	while (!(ADC1->CR & 0x80000000)); // Wait for calibration to finish
	for (int i = 0 ; i < 100 ; i++) {} // Wait for a little while

	ADC1->CR |= 0x00000001; // Enable ADC1 (0x01 - Enable, 0x02 - Disable)
	while (!(ADC1->ISR & 0x00000001)); // Wait until ready

	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 1, ADC_SampleTime_1Cycles5);

	ADC_StartConversion(ADC1); // Start ADC read
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == 0); // Wait for ADC read

	uint16_t x = ADC_GetConversionValue(ADC1);
	return x;
}

void setPinPA0() {
	GPIOA -> MODER &= ~(0x00000001 << (0 * 2));
	GPIOA -> MODER |= (0x00000000 << (0 * 2));

	GPIOA -> PUPDR &= ~(0x00000003 << (0 * 2));
	GPIOA -> PUPDR |= (0x00000002 << (0 * 2));
}

void setPinPA1() {
	GPIOA -> MODER &= ~(0x00000001 << (1 * 2));
	GPIOA -> MODER |= (0x00000000 << (1 * 2));

	GPIOA -> PUPDR &= ~(0x00000003 << (1 * 2));
	GPIOA -> PUPDR |= (0x00000002 << (1 * 2));
}

void initPins() {
	RCC -> AHBENR |= RCC_AHBPeriph_GPIOA;
	setPinPA0();
	setPinPA1();
}
