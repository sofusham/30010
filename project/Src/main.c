#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "ansi.h"
#include "timer.h"
#include "lcd.h"
#include "charset.h"
#include "ball.h"

int main(void)
{
	int dir = 0;
	uart_init(576000);
	configureTimer();
	clrscr();
	window(1440, 640, 11520, 3840);
	ball_t ball_p = {1984, 1024, 2, 0, 0};
	gotoxy(ball_p.x, ball_p.y);
	printf("\xDB");
	gotoxy(ball_p.x - (1 << 7), ball_p.y - (1 << 7));
	printf("\xDB");
	gotoxy(ball_p.x - (1 << 7), ball_p.y + (1 << 7));
	printf("\xDB");

	while(1){
		if (uart_get_count() == 1) {
			dir = string_check(read_uart_data(1));
			centisecond = 0;
		}
		update_spaceship(&ball_p, dir);
		if (centisecond > 20) {
			wind_resistance(&ball_p);
			centisecond = 0;
		}

		//lav en konstant movement der er høj så længe der er forskel på temp_velocity og celocity. Når movement er lav så kører wind_resistance
		//Sæt timeren til 0 ved input fra tastaturet idiot

		gotoxy(14080, 1024);
		printf("velocity: x = %d, y = %d ", ball_p.velX, ball_p.velY);
		dir = 0;
	}
}
