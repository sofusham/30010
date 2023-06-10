#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "stdio.h"
#include "string.h"
#include "stdint.h"
#include "lcd.h"
#include "charset.h"
#include "ansi.h"
#include "timer.h"

int main(void)
{
	int i = 0;
	uart_init(576000);
	lcd_init();
	configureTimer();
	//memset(buffer,0x00,512);

	lcd_write_string("hej", 1);
	lcd_write_string("hej", 2);
	lcd_write_string("hej", 3);
	lcd_write_string("hej", 4);

	while(1) {
		lcd_update(10);
		lcd_push_buffer(buffer);
	}

}
