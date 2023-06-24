/*
 * bullet.c
 *
 *  Created on: 14. jun. 2023
 *      Author: danie
 */
/*
 * bullet.c
 *  Created on: 13. jun. 2023
 *      Author: danie
 */

#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h"

#include "spaceship.h"
#include "ansi.h"
#include "timer.h"
#include "lcd.h"
#include "charset.h"
#include "analogJoystick.h"
#include "draw.h"
#include "position.h"
#include "bullet.h"



void spawnBullet(bullet_t * bullet){

	(*bullet).positionX = 0;
	(*bullet).positionY = 0;
	(*bullet).vectorX = 0;
	(*bullet).vectorY = 0;
	(*bullet).active = 0;

}

void shoot(bullet_t * bullet, spaceship_t * spaceship) {
	(*bullet).positionX = (*spaceship).x;
	(*bullet).positionY = (*spaceship).y;
	(*bullet).active = 1;
	(*bullet).counter = 100;
	switch((*spaceship).rotation){
	case 0:
		(*bullet).vectorX = 0;
		(*bullet).vectorY = -96;
		(*bullet).positionY -= 128;
		break;

	case 1:
		(*bullet).vectorX = 64;
		(*bullet).vectorY = -64;
		(*bullet).positionX += 128;
		(*bullet).positionY -= 128;

		break;

	case 2:
		(*bullet).vectorX = 96;
		(*bullet).vectorY = 0;
		(*bullet).positionX += 128;
		break;

	case 3:
		(*bullet).vectorX = 64;
		(*bullet).vectorY = 64;
		(*bullet).positionX += 128;
		(*bullet).positionY += 128;
		break;

	case 4:
		(*bullet).vectorX = 0;
		(*bullet).vectorY = 96;
		(*bullet).positionY += 128;
		break;

	case 5:
		(*bullet).vectorX = -64;
		(*bullet).vectorY = 64;
		(*bullet).positionY += 128;
		(*bullet).positionX -= 128;
		break;

	case 6:
		(*bullet).vectorX = -96;
		(*bullet).vectorY = 0;
		(*bullet).positionX -= 128;
		break;

	case 7:
		(*bullet).vectorX = -64;
		(*bullet).vectorY = -64;
		(*bullet).positionX -= 128;
		(*bullet).positionY -= 128;
		break;
	}
	gotoxy((*bullet).positionX,(*bullet).positionY);
	printf("@");

}

void moveBullet(bullet_t * bullet) {
	if((*bullet).active){
		(*bullet).nextPosX = (*bullet).positionX + (*bullet).vectorX;
		if((*bullet).nextPosX > (128*190)) {
			(*bullet).nextPosX = 0;
			clrscr();
		} else if((*bullet).nextPosX < 0) {
			(*bullet).nextPosX = 128*190;
			clrscr();
		}

		(*bullet).nextPosY = (*bullet).positionY + (*bullet).vectorY;
		if((*bullet).nextPosY > (128*55)) {
			(*bullet).nextPosY = 0;
			clrscr();
		} else if((*bullet).nextPosY < 0) {
			(*bullet).nextPosY = 128*55;
			clrscr();
		}
		gotoxy((*bullet).positionX, (*bullet).positionY);
		printf(" ");
		(*bullet).positionX = (*bullet).nextPosX;
		(*bullet).positionY = (*bullet).nextPosY;
		gotoxy((*bullet).positionX, (*bullet).positionY);
		printf("@");
		(*bullet).counter = ((*bullet).counter-1);
		if(((*bullet).counter) == 0){ // bullet decay
			gotoxy((*bullet).positionX, (*bullet).positionY);
			printf(" ");
			spawnBullet(&(*bullet)); //resets bullet to inactive state
		}
	 }
}
