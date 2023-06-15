/*
 * ball.c
 *
 *  Created on: 12. jun. 2023
 *      Author: sofus
 */
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "ball.h"
#include "ansi.h"

void update_spaceship(ball_t * ball_p, int dir) {
	int32_t tempX = (*ball_p).x;
	int32_t tempY = (*ball_p).y;
	int8_t tempR = (*ball_p).rotation;

	switch(dir) {
	case 1:
		update_velocity(&(*ball_p));
		break;
	case 2:
		(*ball_p).rotation--;
		if ((*ball_p).rotation < 0) {(*ball_p).rotation = 7;}
		break;
	case 4:
		(*ball_p).rotation++;
		if ((*ball_p).rotation > 7) {(*ball_p).rotation = 0;}
		break;
	}
	(*ball_p).x += (*ball_p).velX;
	(*ball_p).y += (*ball_p).velY;
	if (tempX != (*ball_p).x || tempY != (*ball_p).y || tempR != (*ball_p).rotation) {draw_new_spaceship(&(*ball_p), tempX, tempY, tempR);}
}

void wind_resistance(ball_t * ball_p) {
	/*if ((*ball_p).velX <= -2) {(*ball_p).velX += 2;}
	else if ((*ball_p).velX >= 2) {(*ball_p).velX -= 2;}
	else if ((*ball_p).velX < 2 && (*ball_p).velX > -2) {(*ball_p).velX = 0;}

	if ((*ball_p).velY <= -2) {(*ball_p).velY += 2;}
	else if ((*ball_p).velY >= 2) {(*ball_p).velY -= 2;}
	else if ((*ball_p).velY < 2 && (*ball_p).velY > -2) {(*ball_p).velY = 0;}*/

	if ((*ball_p).velX >= 1) {(*ball_p).velX -= 1;}
	else if ((*ball_p).velX <= - 1) {(*ball_p).velX += 1;}

	if ((*ball_p).velY >= 1) {(*ball_p).velY -= 1;}
	else if ((*ball_p).velY <= - 1) {(*ball_p).velY += 1;}
}

void update_velocity(ball_t * ball_p) {
	switch((*ball_p).rotation) {
	case 0:
		(*ball_p).velY -= 4;
		break;
	case 1:
		(*ball_p).velX += 4;
		(*ball_p).velY -= 4;
		break;
	case 2:
		(*ball_p).velX += 4;
		break;
	case 3:
		(*ball_p).velX += 4;
		(*ball_p).velY += 4;
		break;
	case 4:
		(*ball_p).velY += 4;
		break;
	case 5:
		(*ball_p).velX -= 4;
		(*ball_p).velY += 4;
		break;
	case 6:
		(*ball_p).velX -= 4;
		break;
	case 7:
		(*ball_p).velX -= 4;
		(*ball_p).velY -= 4;
		break;
	}
}

void draw_new_spaceship(ball_t * ball_p, int32_t tempX, int32_t tempY, int8_t tempR) {
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
	switch((*ball_p).rotation) {
	case 0:
		gotoxy((*ball_p).x - (1 << 7), (*ball_p).y + (1 << 7));
		printf("\xDB");
		gotoxy((*ball_p).x, (*ball_p).y);
		printf("\xDB");
		gotoxy((*ball_p).x + (1 << 7), (*ball_p).y + (1 << 7));
		printf("\xDB");
		break;
	case 1:
		gotoxy((*ball_p).x - (1 << 7), (*ball_p).y);
		printf("\xDB");
		gotoxy((*ball_p).x, (*ball_p).y);
		printf("\xDB");
		gotoxy((*ball_p).x, (*ball_p).y + (1 << 7));
		printf("\xDB");
		break;
	case 2:
		gotoxy((*ball_p).x - (1 << 7), (*ball_p).y - (1 << 7));
		printf("\xDB");
		gotoxy((*ball_p).x, (*ball_p).y);
		printf("\xDB");
		gotoxy((*ball_p).x - (1 << 7), (*ball_p).y + (1 << 7));
		printf("\xDB");
		break;
	case 3:
		gotoxy((*ball_p).x, (*ball_p).y - (1 << 7));
		printf("\xDB");
		gotoxy((*ball_p).x - (1 << 7), (*ball_p).y);
		printf("\xDB");
		gotoxy((*ball_p).x, (*ball_p).y);
		printf("\xDB");
		break;
	case 4:
		gotoxy((*ball_p).x - (1 << 7), (*ball_p).y - (1 << 7));
		printf("\xDB");
		gotoxy((*ball_p).x, (*ball_p).y);
		printf("\xDB");
		gotoxy((*ball_p).x + (1 << 7), (*ball_p).y - (1 << 7));
		printf("\xDB");
		break;
	case 5:
		gotoxy((*ball_p).x, (*ball_p).y - (1 << 7));
		printf("\xDB");
		gotoxy((*ball_p).x, (*ball_p).y);
		printf("\xDB");
		gotoxy((*ball_p).x + (1 << 7), (*ball_p).y);
		printf("\xDB");
		break;
	case 6:
		gotoxy((*ball_p).x + (1 << 7), (*ball_p).y - (1 << 7));
		printf("\xDB");
		gotoxy((*ball_p).x, (*ball_p).y);
		printf("\xDB");
		gotoxy((*ball_p).x + (1 << 7), (*ball_p).y + (1 << 7));
		printf("\xDB");
		break;
	case 7:
		gotoxy((*ball_p).x, (*ball_p).y + (1 << 7));
		printf("\xDB");
		gotoxy((*ball_p).x, (*ball_p).y);
		printf("\xDB");
		gotoxy((*ball_p).x + (1 << 7), (*ball_p).y);
		printf("\xDB");
		break;
	}
}
