#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "joystick.h"
#include "stdio.h"
#include "stdint.h"
#include "timer.h"
#include "ansi.h"
#include "string.h"

int main(void) {
	/*volatile temp;

	int32_t second = 0;
	int32_t minute = 0;
	int32_t hour = 0;
	int32_t stop = 0;
	int32_t tempJoy = 0x00;
	int32_t split1centi = 0;
	int32_t split1sec = 0;
	int32_t split1min = 0;
	int32_t split1hour = 0;

	uart_init(576000);
	clrscr();
	initPins();

	configureTimer();
	window(10, 5, 42, 10);
	gotoxy(12, 7);
	printf("Time since start:");
	gotoxy(12, 8);
	printf("Split time 1:");
	gotoxy(12, 9);
	printf("Split time 2:");
	gotoxy(31,8);
	printf("%d:%d:%d.%d", split1hour, split1min, split1sec, split1centi);
	gotoxy(31,9);
	printf("0:0:0.0");

	while(1) {
		if( (centisecond > 99) ) {
			second++;
			centisecond = 0;
		}
		if(second > 59){
			minute++;
			second = 0;
		}
		if(minute > 59){
			hour++;
			minute = 0;
		}
		if (centisecond != temp) {
			gotoxy(31, 7);
			printf("%d:%d:%d.%d", hour, minute, second, centisecond);
		}
		if (readJoystick() == 0x04 && tempJoy != 0x04) {
			int32_t split1centi = centisecond;
			int32_t split1sec = second;
			int32_t split1min = minute;
			int32_t split1hour = hour;
			gotoxy(31,8);
			printf("%d:%d:%d.%d", split1hour, split1min, split1sec, split1centi);
		}
		if (readJoystick() == 0x07 && tempJoy != 0x07) {
			gotoxy(31,9);
			printf("%d:%d:%d.%d", hour, minute, second, centisecond);
		}
		if (readJoystick() == 0x10 && tempJoy != 0x10){
			TIM15 -> DIER ^= 0x0001;
		}


		temp = centisecond;
		tempJoy = readJoystick();

	uart_init(576000);

	clrscr();
	gotoxy(0,0);
	//printf("\n%d", stringCheck());
	printf("\n%d", stringCheck(read_uart_data(6)));
	*/
	volatile temp;

	int32_t second = 0;
	int32_t minute = 0;
	int32_t hour = 0;
	int32_t stop = 0;
	int32_t tempJoy = 0x00;
	int32_t split1centi = 0;
	int32_t split1sec = 0;
	int32_t split1min = 0;
	int32_t split1hour = 0;
	int32_t split2centi = 0;
	int32_t split2sec = 0;
	int32_t split2min = 0;
	int32_t split2hour = 0;
	int32_t numChar;

	uart_init(576000);
	clrscr();
	initPins();

	configureTimer();
	window(10, 5, 44, 10);
	gotoxy(12, 7);
	printf("Time since start:");
	gotoxy(12, 8);
	printf("Split time 1:");
	gotoxy(12, 9);
	printf("Split time 2:");
	gotoxy(31,8);
	printf("%02d:%02d:%02d.%02d", split1hour, split1min, split1sec, split1centi);
	gotoxy(31,9);
	printf("00:00:00.00");
	while(1) {
		if( (centisecond > 99) ) {
			second++;
			centisecond = 0;
		}
		if(second > 59){
			minute++;
			second = 0;
		}
		if(minute > 59){
			hour++;
			minute = 0;
		}
		if (centisecond != temp) {
			gotoxy(31, 7);
			printf("%02d:%02d:%02d.%02d", hour, minute, second, centisecond);
			gotoxy(42,7);
			printf("\x20");
		}
		numChar = uart_get_count();
		if (numChar == 1) {
			switch (stringCheck(read_uart_data(1))) {
				case 1:
					TIM15 -> DIER &= ~(0x0001);
					break;
				case 2:
					TIM15 -> DIER |= 0x0001;
					break;
				case 3:
					split1centi = centisecond;
					split1sec = second;
					split1min = minute;
					split1hour = hour;
					gotoxy(31,8);
					printf("%02d:%02d:%02d.%02d", split1hour, split1min, split1sec, split1centi);
					gotoxy(42,8);
					printf("\x20");
					break;
				case 4:
					split2centi = centisecond;
					split2sec = second;
					split2min = minute;
					split2hour = hour;
					gotoxy(31,9);
					printf("%02d:%02d:%02d.%02d", split2hour, split2min, split2sec, split2centi);
					gotoxy(42,9);
					printf("\x20");
					break;
				case 5:
					hour = 0; minute = 0; second = 0; centisecond = 0;
					gotoxy(31, 7);
					printf("%02d:%02d:%02d.%02d", hour, minute, second, centisecond);
					split1centi = 0; split1sec = 0; split1min = 0; split1hour = 0;
					gotoxy(31,8);
					printf("%02d:%02d:%02d.%02d", split1hour, split1min, split1sec, split1centi);
					gotoxy(31,9);
					split2centi = 0; split2sec = 0; split2min = 0; split1hour = 0;
					printf("%02d:%02d:%02d.%02d", split2hour, split2min, split2sec, split2centi);
					break;
			}
		}
		temp = centisecond;
		tempJoy = readJoystick();
	}
}
