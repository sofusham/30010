#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "adc.h"
#include "ansi.h"
#include "charset.h"
#include "timer.h"
#include "lcd.h"

int main(void)
{
	char str1[9];
	char str2[9];

	int16_t adc1, adc2;
	uart_init(576000);
	configureADC();
	initPins();
	lcd_init();
	configureTimer();

	while(1) {
		adc1 = measurePA0();
		adc2 = measurePA1();
		printf("%04d, %04d\n", adc1, adc2);

		sprintf(str1, "x = %04d", adc1);
		sprintf(str2, "y = %04d", adc2);

		lcd_write_string(str1, 1);
		lcd_write_string(str2, 2);

		for (int i = 0 ; i < 2000 ; i++)

		lcd_push_buffer(buffer);
	}
}
