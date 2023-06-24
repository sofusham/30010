#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "stdio.h"
#include "stdint.h"
#include "lcd.h"
#include "charset.h"
#include "timer.h"

volatile char buffer[512] = {0x7C, 0x0A, 0x09, 0x0A, 0x7C};
volatile int flag = 0;

void lcd_write_string(char * slice, uint8_t line) {
	int i, j;
	for (i = 0; slice[i]; i++) {
		for (j = 0; j < 5; j++) {
			buffer[j + ((line - 1)*128) + (5*i)] = character_data[slice[i] - 32][j];
		}
	}
}

void lcd_update(int s) {
	if (flag == s) {
		shift_buffer();
		flag = 0;
	}

}

void shift_buffer(int line) {
	int i, j;
	char temp;
	temp = buffer[0];
	for (j = 0; j < 127; j++) {
		buffer[j] = buffer[j + 1];
	}
	buffer[127] = temp;


}
