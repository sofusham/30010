/*
 * spaceship.c
 *
 *  Created on: 12. jun. 2023
 *      Author: sofus
 */
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "spaceship.h"
#include "ansi.h"
#include "timer.h"
#include "analogJoystick.h"

void all_spaceship(spaceship_t * spaceship_p, int16_t *prevRot, int16_t *curRot) {
	//Does everything to move the spacehsip
	update_spaceship(&(*spaceship_p), prevRot, curRot);
	if (centisecond > 20) {
		wind_resistance(&(*spaceship_p));
		centisecond = 0;
	}
}
void update_spaceship(spaceship_t * spaceship_p, int16_t *prevRot, int16_t *curRot) {
	//Creates temporary variables to remove old spaceship
	int32_t tempX = (*spaceship_p).x;
	int32_t tempY = (*spaceship_p).y;
	int8_t tempR = (*spaceship_p).rotation;

	//Updates velocity and orientation
	if (measurePA7()) {update_velocity(&(*spaceship_p));}
	if (curRot != prevRot) {
		if (curRot == 1) {
			(*spaceship_p).rotation++;
			if ((*spaceship_p).rotation > 7) {(*spaceship_p).rotation = 0;}
		}
		else if (curRot == 2) {
			(*spaceship_p).rotation--;
			if ((*spaceship_p).rotation < 0) {(*spaceship_p).rotation = 7;}
		}
	}

	//Updates position
	(*spaceship_p).x += (*spaceship_p).velX;
	(*spaceship_p).y += (*spaceship_p).velY;

	wrapping(&(*spaceship_p));

	draw_new_spaceship(&(*spaceship_p), tempX, tempY, tempR);
}

void wrapping(spaceship_t * spaceship_p) {
	//Wraps spaceship from one side to another
	if ((*spaceship_p).x > 128 * 190) {
		(*spaceship_p).x = 0;
		clrscr();
	}
	else if ((*spaceship_p).x < 0) {
		(*spaceship_p).x = 128 * 190;
		clrscr();
	}
	if ((*spaceship_p).y > 128 * 55) {
		(*spaceship_p).y = 0;
		clrscr();
	}
	else if ((*spaceship_p).y < 0) {
		(*spaceship_p).y = 128* 55;
		clrscr();
	}
}

void wind_resistance(spaceship_t * spaceship_p) {
	if ((*spaceship_p).velX >= 8) {(*spaceship_p).velX -= 8;}
	else if ((*spaceship_p).velX <= -8) {(*spaceship_p).velX += 8;}
	else if ((*spaceship_p).velX < 8 && (*spaceship_p).velX > -8) {(*spaceship_p).velX = 0;}

	if ((*spaceship_p).velY >= 8) {(*spaceship_p).velY -= 8;}
	else if ((*spaceship_p).velY <= -8) {(*spaceship_p).velY += 8;}
	else if ((*spaceship_p).velY < 8 && (*spaceship_p).velY > -8) {(*spaceship_p).velY = 0;}
}

void update_velocity(spaceship_t * spaceship_p) {
	switch((*spaceship_p).rotation) {
	case 0:
		(*spaceship_p).velY -= 8;
		break;
	case 1:
		(*spaceship_p).velX += 8;
		(*spaceship_p).velY -= 8;
		break;
	case 2:
		(*spaceship_p).velX += 8;
		break;
	case 3:
		(*spaceship_p).velX += 8;
		(*spaceship_p).velY += 8;
		break;
	case 4:
		(*spaceship_p).velY += 8;
		break;
	case 5:
		(*spaceship_p).velX -= 8;
		(*spaceship_p).velY += 8;
		break;
	case 6:
		(*spaceship_p).velX -= 8;
		break;
	case 7:
		(*spaceship_p).velX -= 8;
		(*spaceship_p).velY -= 8;
		break;
	}

	//Speed limit
	if ((*spaceship_p).velX > 90) {(*spaceship_p).velX = 90; }
	else if ((*spaceship_p).velX < -90) {(*spaceship_p).velX = -90; }
	if ((*spaceship_p).velY > 75) {(*spaceship_p).velY = 75; }
	else if ((*spaceship_p).velY < -75) {(*spaceship_p).velY = -75;}
}

void draw_new_spaceship(spaceship_t * spaceship_p, int32_t tempX, int32_t tempY, int8_t tempR) {
	// clearing the old spaceship
	switch (tempR) {
	case 0:
		gotoxy(tempX - (1 << 7), tempY + (1 << 7));
		printf(" ");
		gotoxy(tempX, tempY);
		printf(" ");
		gotoxy(tempX + (1 << 7), tempY + (1 << 7));
		printf(" ");
		break;
	case 1:
		gotoxy(tempX - (1 << 7), tempY);
		printf(" ");
		gotoxy(tempX, tempY);
		printf(" ");
		gotoxy(tempX, tempY + (1 << 7));
		printf(" ");
		break;
	case 2:
		gotoxy(tempX - (1 << 7), tempY - (1 << 7));
		printf(" ");
		gotoxy(tempX, tempY);
		printf(" ");
		gotoxy(tempX - (1 << 7), tempY + (1 << 7));
		printf(" ");
		break;
	case 3:
		gotoxy(tempX, tempY - (1 << 7));
		printf(" ");
		gotoxy(tempX, tempY);
		printf(" ");
		gotoxy(tempX - (1 << 7), tempY);
		printf(" ");
		break;
	case 4:
		gotoxy(tempX - (1 << 7), tempY - (1 << 7));
		printf(" ");
		gotoxy(tempX, tempY);
		printf(" ");
		gotoxy(tempX + (1 << 7), tempY - (1 << 7));
		printf(" ");
		break;
	case 5:
		gotoxy(tempX, tempY - (1 << 7));
		printf(" ");
		gotoxy(tempX, tempY);
		printf(" ");
		gotoxy(tempX + (1 << 7), tempY);
		printf(" ");
		break;
	case 6:
		gotoxy(tempX + (1 << 7), tempY - (1 << 7));
		printf(" ");
		gotoxy(tempX, tempY);
		printf(" ");
		gotoxy(tempX + (1 << 7), tempY + (1 << 7));
		printf(" ");
		break;
	case 7:
		gotoxy(tempX, tempY + (1 << 7));
		printf(" ");
		gotoxy(tempX, tempY);
		printf(" ");
		gotoxy(tempX + (1 << 7), tempY);
		printf(" ");
		break;
	}

	//printing new spaceship
	switch((*spaceship_p).rotation) {
	case 0:
		gotoxy((*spaceship_p).x - (1 << 7), (*spaceship_p).y + (1 << 7));
		printf("\xDB");
		gotoxy((*spaceship_p).x, (*spaceship_p).y);
		printf("\xDB");
		gotoxy((*spaceship_p).x + (1 << 7), (*spaceship_p).y + (1 << 7));
		printf("\xDB");
		break;
	case 1:
		gotoxy((*spaceship_p).x - (1 << 7), (*spaceship_p).y);
		printf("\xDB");
		gotoxy((*spaceship_p).x, (*spaceship_p).y);
		printf("\xDB");
		gotoxy((*spaceship_p).x, (*spaceship_p).y + (1 << 7));
		printf("\xDB");
		break;
	case 2:
		gotoxy((*spaceship_p).x - (1 << 7), (*spaceship_p).y - (1 << 7));
		printf("\xDB");
		gotoxy((*spaceship_p).x, (*spaceship_p).y);
		printf("\xDB");
		gotoxy((*spaceship_p).x - (1 << 7), (*spaceship_p).y + (1 << 7));
		printf("\xDB");
		break;
	case 3:
		gotoxy((*spaceship_p).x, (*spaceship_p).y - (1 << 7));
		printf("\xDB");
		gotoxy((*spaceship_p).x - (1 << 7), (*spaceship_p).y);
		printf("\xDB");
		gotoxy((*spaceship_p).x, (*spaceship_p).y);
		printf("\xDB");
		break;
	case 4:
		gotoxy((*spaceship_p).x - (1 << 7), (*spaceship_p).y - (1 << 7));
		printf("\xDB");
		gotoxy((*spaceship_p).x, (*spaceship_p).y);
		printf("\xDB");
		gotoxy((*spaceship_p).x + (1 << 7), (*spaceship_p).y - (1 << 7));
		printf("\xDB");
		break;
	case 5:
		gotoxy((*spaceship_p).x, (*spaceship_p).y - (1 << 7));
		printf("\xDB");
		gotoxy((*spaceship_p).x, (*spaceship_p).y);
		printf("\xDB");
		gotoxy((*spaceship_p).x + (1 << 7), (*spaceship_p).y);
		printf("\xDB");
		break;
	case 6:
		gotoxy((*spaceship_p).x + (1 << 7), (*spaceship_p).y - (1 << 7));
		printf("\xDB");
		gotoxy((*spaceship_p).x, (*spaceship_p).y);
		printf("\xDB");
		gotoxy((*spaceship_p).x + (1 << 7), (*spaceship_p).y + (1 << 7));
		printf("\xDB");
		break;
	case 7:
		gotoxy((*spaceship_p).x, (*spaceship_p).y + (1 << 7));
		printf("\xDB");
		gotoxy((*spaceship_p).x, (*spaceship_p).y);
		printf("\xDB");
		gotoxy((*spaceship_p).x + (1 << 7), (*spaceship_p).y);
		printf("\xDB");
		break;
	}
}
