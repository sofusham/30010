#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "spaceship.h"
#include "ansi.h"
#include "lcd.h"
#include "charset.h"
#include "analogJoystick.h"
#include "draw.h"
#include "position.h"
#include "bullet.h"
#include "string.h"
#include "timer.h"
#include "timer2.h"
#include "time.h"
#include "menu.h"
#include "led.h"

void lcdInfo(uint32_t lives, char lifestring[], uint32_t score, char scorestring[], uint32_t highscore, char highscorestring[]){
	memset(buffer, 0x00, 512);
	sprintf(lifestring, "Lives: %d", lives);
	lcd_write_string(lifestring, 1);
	lcd_push_buffer(buffer);
	sprintf(scorestring, "Score: %d", score);
	lcd_write_string(scorestring, 3);
	sprintf(highscorestring, "High score: %d", highscore);
	lcd_write_string(highscorestring, 4);
	lcd_push_buffer(buffer);
}

int main(void)
{
	int32_t score = 0;
	int32_t highscore = 0;
	uint32_t lives = 3;
	char highscorestring[12];
	int8_t asteroids_gone;
	int8_t alien_gone;

	uart_init(576000);
	configureTimer();
	clrscr();
	initLED();
	lcd_init();
	initPins();
	configureADC();
	configure_timer2();

	spaceship_t spaceship_p = {1984, 1024, 2, 0, 0};

	powerup_t powerup;
	powerup.x = 0;
	powerup.y = 0;
	powerup.active = 0;
	powerup.type = 1;

	while(1) {
		//Loop for coming back to start menu when dead
		start_menu();

		//Spaceship in startposition
		spaceship_p.x = 12169;
		spaceship_p.y = 3520;
		spaceship_p.rotation = 2;
		spaceship_p.velX = 0;
		spaceship_p.velY = 0;
		gotoxy(spaceship_p.x, spaceship_p.y);
		printf("\xDB");
		gotoxy(spaceship_p.x - (1 << 7), spaceship_p.y - (1 << 7));
		printf("\xDB");
		gotoxy(spaceship_p.x - (1 << 7), spaceship_p.y + (1 << 7));
		printf("\xDB");


		while(1) {
			//Loop initializing game first time and when alien and asteroids are gone

			//For joystick edge detection
			int16_t prevRot = 0;
			int16_t curRot;
			int16_t prevShot = 0;
			int16_t curShot;
			clrscr();

			asteroids_gone = 0;
			alien_gone = 0;
			char lifestring[8];
			char scorestring[8];
			asteroid_t asteroids[8];
			int8_t bulletCount = 0;
			bullet_t bullet[8];
			for (int i = 0; i < 8; i++) {
				spawnBullet(&bullet[i]);
			}

			for(int i = 0; i < 8; i++){
				asteroids[i].x = rand() % 24320;
				asteroids[i].y = rand() % 7040;
				asteroids[i].velX = rand() % 32;
				asteroids[i].velY = rand() % 32;
				if(asteroids[i].velX % 2 == 0){
					asteroids[i].velX = -1*(asteroids[i].velX);
				}
				if(asteroids[i].velY % 2 == 0){
					asteroids[i].velY = -1*(asteroids[i].velY);
				}

				if(i == 5){
					asteroids[i].hasPowerup = 1;
				} else {
					asteroids[i].hasPowerup = 0;
				}
				asteroids[i].destroyed = 0;
			}

			alien_t alien;
			alien.x = rand() % 24320;
			alien.y = rand() % 7040;
			alien.active = 1;


			lcdInfo(lives, &lifestring, score, &scorestring, highscore, &highscorestring);

			while(1) {
				//Loop moving objects and taking input

				stop_buzzer();
				curRot = measurePA6();
				curShot = getPF1();

				all_spaceship(&spaceship_p, prevRot, curRot);
				for (int l = 0; l < 8; l++) {
					clearAsteroid(&asteroids[l]);
					calculateNextAst(&asteroids[l]);
					updatePosAst(&asteroids[l]);
					drawAsteroid(&asteroids[l]);
				}

				if (curShot > prevShot) {
					set_freq(500);
					shoot(&bullet[bulletCount], &spaceship_p);
					bulletCount++;
					if (bulletCount > 7) { bulletCount = 0;}
				}

				clearAlien(&alien);
				moveAlien(&alien, &spaceship_p);
				drawAlien(&alien);

				for (int j = 0; j < 8; j++) {
					moveBullet(&bullet[j]);
				}

				for (int k = 0; k < 8; k++) {
					if (shipAsteroidCollision(&spaceship_p, &asteroids[k])) {
						asteroids_gone++;
						lives--;
						score = score + 40;
						if (score > highscore) {highscore = score; }
						lcdInfo(lives, &lifestring, score, &scorestring, highscore, &highscorestring);
					}
				}

				if (shipAlienCollision(&spaceship_p, &alien)) {
					alien_gone++;
					lives--;
					lcdInfo(lives, &lifestring, score, &scorestring, highscore, &highscorestring);
				}

				for (int j = 0; j < 8; j++) {
					for (int a = 0; a < 8; a++) {
						if (asteroidBulletCollision(&asteroids[a], &bullet[j], &spaceship_p)) {
							asteroids_gone++;
							score += 40;
							if (asteroids[a].hasPowerup) {
								powerup.x = asteroids[a].x;
								powerup.y = asteroids[a].y;
								powerup.active = 1;
								gotoxy(powerup.x, asteroids[a].y);
								printf("!");
							}
							lcdInfo(lives, &lifestring, score, &scorestring, highscore, &highscorestring);
						}
					}
				}

				for (int j = 0; j < 8; j++) {
					if (bulletAlienCollision(&bullet[j], &alien, &spaceship_p)) {
						alien_gone++;
						score += 100;
						lcdInfo(lives, &lifestring, score, &scorestring, highscore, &highscorestring);
					}
				}

				pickupPowerup(&spaceship_p, &powerup, lives);
				if (spaceship_p.infiniteRange) {
					for (int j = 0; j < 8; j++) {
						bullet[j].counter = 20;
					}
				}



				prevRot = curRot;
				prevShot = curShot;

				//boss key
				if (uart_get_count() == 1) {
					if (string_check(read_uart_data(1)) == 1) {
						boss_menu();
						clrscr();
					}
				}

				if (score > highscore) { highscore = score; }
				lcdInfo(lives, &lifestring, score, &scorestring, highscore, &highscorestring);
				if (lives == 0) {
					setLED(lives);
					lives = 3;
					score = 0;
					spaceship_p.infiniteRange = 0;
					spaceship_p.stoppingPower = 0;
					break;
				}

				drawPowerup(&powerup);
				setLED(lives);

				//Breaks to loop generating new asteroids and alien
				if (asteroids_gone == 8 && alien_gone) { break; }
			}
			// break to loop with the start menu if condition false
			if (asteroids_gone == 8 && alien_gone) {}
			else {
				death_menu();
				break;
			}

		}

	}
}
