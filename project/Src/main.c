#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "ansi.h"
#include "timer.h"
#include "lcd.h"
#include "charset.h"
#include "ball.h"
#include "draw.h"
#include "position.h"

void lcdInfo(uint32_t lives, char lifestring[], uint32_t score, char scorestring[]){
	memset(buffer, 0x00, 512);
	sprintf(lifestring, "Lives: %d", lives);
	lcd_write_string(lifestring, 1);
	lcd_push_buffer(buffer);
	sprintf(scorestring, "Score: %d", score);
	lcd_write_string(scorestring, 3);
	lcd_push_buffer(buffer);
}

int main(void)
{
	int dir = 0;
	uint32_t lives = 3;
	char lifestring[8];
	uint32_t score = 0;
	char scorestring[8];
	int count = 0;
	asteroid_t asteroids;

	uart_init(576000);
	configureTimer();
	clrscr();
	lcd_init();
	//window(1440, 640, 11520, 3840);
	spaceship_t spaceship_p = {1984, 1024, 2, 0, 0};
	gotoxy(spaceship_p.x, spaceship_p.y);
	printf("\xDB");
	gotoxy(spaceship_p.x - (1 << 7), spaceship_p.y - (1 << 7));
	printf("\xDB");
	gotoxy(spaceship_p.x - (1 << 7), spaceship_p.y + (1 << 7));
	printf("\xDB");

	asteroids.x = 384;
	asteroids.y = 384;
	asteroids.velX = 1;
	asteroids.velY = 1;
	asteroids.destroyed = 0;

	lcdInfo(lives, &lifestring, score, &scorestring);

	while(1){
		/*if (uart_get_count() == 1) {
			dir = string_check(read_uart_data(1));
			centisecond = 0;
		}
		update_spaceship(&spaceship_p, dir);
		if (centisecond > 20) {
			wind_resistance(&spaceship_p);
			centisecond = 0;
		}

		//lav en konstant movement der er høj så længe der er forskel på temp_velocity og celocity. Når movement er lav så kører wind_resistance
		//Sæt timeren til 0 ved input fra tastaturet idiot

		gotoxy(14080, 1024);
		printf("velocity: x = %d, y = %d ", spaceship_p.velX, spaceship_p.velY);
		*dir = 0;*/
		do_the_thing(&spaceship_p, dir);
		calculateNextAst(&asteroids);
		updatePosAst(&asteroids);
		drawAsteroid(&asteroids);

		if(shipAsteroidCollision(&spaceship_p, &asteroids)){
			gotoxy(1600,1600);
			printf("Colission!");
			lives = lives - 1;
			score = score +40;
			lcdInfo(lives, &lifestring, score, &scorestring);
		}
		//for(int i = 0; i <1500000; i++){}
		clearAsteroid(&asteroids);

	}
}
