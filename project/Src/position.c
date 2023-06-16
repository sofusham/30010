#include "stdio.h"
#include "stm32f30x_conf.h"
#include "ansi.h"
#include "30010_io.h"
#include "stdint.h"
#include "spaceship.h"
#include "draw.h"
#include "lcd.h"
#include "charset.h"
#include "timer.h"



void calculateNextAst( asteroid_t * asteroid){
	(*asteroid).nextPosX = (*asteroid).x + (*asteroid).velX;
	(*asteroid).nextPosY = (*asteroid).y + (*asteroid).velY;
	if((*asteroid).nextPosX > 128*190){
		(*asteroid).nextPosX = 0;
	} else if((*asteroid).nextPosX < 0) {
		(*asteroid).nextPosX = 128*190;
	}
	if((*asteroid).nextPosY > 128*55){
		(*asteroid).nextPosY = 0;
	} else if((*asteroid).nextPosY < 0) {
		(*asteroid).nextPosY = 128*55;
	}
}

void calculateNextShip( spaceship_t * spaceship){
	(*spaceship).nextPosX = (*spaceship).x + (*spaceship).velX;
	(*spaceship).nextPosY = (*spaceship).y + (*spaceship).velY;
	if((*spaceship).nextPosX > 128*190){
		(*spaceship).nextPosX = 0;
	} else if((*spaceship).nextPosX < 0) {
		(*spaceship).nextPosX = 128*190;
	}
	if((*spaceship).nextPosY > 128*55){
		(*spaceship).nextPosY = 0;
	} else if((*spaceship).nextPosY < 0) {
		(*spaceship).nextPosY = 128*55;
	}
}

void updatePosAst( asteroid_t * asteroid){

	(*asteroid).x = (*asteroid).nextPosX;
	(*asteroid).y = (*asteroid).nextPosY;
}

void updatePosShip( spaceship_t * spaceship){

	(*spaceship).x = (*spaceship).nextPosX;
	(*spaceship).y = (*spaceship).nextPosY;
}

int32_t shipAsteroidCollision(spaceship_t * spaceship, asteroid_t * asteroid ){
	 	int32_t astXMax = (*asteroid).x+128;
		int32_t astXMin = (*asteroid).x-128;
		int32_t astYMax = (*asteroid).y+128;
		int32_t astYMin = (*asteroid).y-128;
		int32_t withinX = (((*spaceship).x <  astXMax) && ((*spaceship).x >  astXMin)) || (((*spaceship).x+32 <  astXMax) && ((*spaceship).x+32 >  astXMin));
		int32_t withinY = ((*spaceship).y <  astYMax) && ((*spaceship).y >  astYMin);

	if(withinX && withinY && !((*asteroid).destroyed)){
		(*asteroid).destroyed = 1;
		return 1;
	} else {
		return 0;
	}
}

int32_t asteroidBulletCollision(asteroid_t * asteroid, bullet_t * bullet){
 	int32_t astXMax = (*asteroid).x+256;
	int32_t astXMin = (*asteroid).x-256;
	int32_t astYMax = (*asteroid).y+256;
	int32_t astYMin = (*asteroid).y-256;
	int32_t withinX = ((*bullet).x <  astXMax) && ((*bullet).x >  astXMin);
	int32_t withinY = ((*bullet).y <  astYMax) && ((*bullet).y >  astYMin);
	if(withinX && withinY && !((*asteroid).destroyed)){
		(*asteroid).destroyed = 1;
		return 1;
	} else {
		return 0;
	}
}
