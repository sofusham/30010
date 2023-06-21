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
#include "bullet.h"
#include "position.h"


void calculateNextAst( asteroid_t * asteroid){
	(*asteroid).nextPosX = (*asteroid).x + (*asteroid).velX;
	(*asteroid).nextPosY = (*asteroid).y + (*asteroid).velY;
	if((*asteroid).nextPosX > 128*190){ //Wrapping for x-coordinates
		(*asteroid).nextPosX = 0;
		clrscr();
	} else if((*asteroid).nextPosX < 0) {
		(*asteroid).nextPosX = 128*190;
		clrscr();
	}
	if((*asteroid).nextPosY > 128*55){ //Wrapping for y-coordinates
		(*asteroid).nextPosY = 0;
		clrscr();
	} else if((*asteroid).nextPosY < 0) {
		(*asteroid).nextPosY = 128*55;
		clrscr();
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

int8_t shipAsteroidCollision(spaceship_t * spaceship, asteroid_t * asteroid ){
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

int8_t asteroidBulletCollision(asteroid_t * asteroid, bullet_t * bullet, spaceship_t * spaceship){
	if((*bullet).active && !((*asteroid).destroyed)){
		int32_t astXMax = (*asteroid).x+256;
		int32_t astXMin = (*asteroid).x-256;
		int32_t astYMax = (*asteroid).y+128;
		int32_t astYMin = (*asteroid).y-128;
		int32_t withinX = ((*bullet).positionX <  astXMax) && ((*bullet).positionX >  astXMin);
		int32_t withinY = ((*bullet).positionY <  astYMax) && ((*bullet).positionY >  astYMin);
		if(withinX && withinY){ //Check if bullet collides with asteroid
			(*asteroid).destroyed = 1;
			if(!(*spaceship).stoppingPower){
				(*bullet).active = 0;
			}
			return 1;
		} else {
			int32_t gravXMax = (*asteroid).x+640;
			int32_t gravXMin = (*asteroid).x-640; //Determines bounds of gravitational field
			int32_t gravYMax = (*asteroid).y+512;
			int32_t gravYMin = (*asteroid).y-512;
			int8_t withinGravityFieldX = (((*bullet).positionX <  gravXMax) && ((*bullet).positionX >  gravXMin)); // Check if bullet is in gravitational field
			int8_t withinGravityFieldY = (((*bullet).positionY <  gravYMax) && ((*bullet).positionY >  gravYMin));
			if(withinGravityFieldX && withinGravityFieldY){
				if((*bullet).positionX < (*asteroid).x){ //Accelerates bullets in the field
					(*bullet).vectorX += 8;
				} else if((*bullet).positionX > (*asteroid).x) {
					(*bullet).vectorX -= 8;
				}
				if((*bullet).positionY < (*asteroid).y){
					(*bullet).vectorY += 8;
				} else if((*bullet).positionY > (*asteroid).y) {
					(*bullet).vectorY -= 8;
				}
			}
			return 0;
		}
	} else {
		return 0;
	}

}

void moveAlien(alien_t * alien, spaceship_t * spaceship){
	if((*alien).active){
		if(((*alien).x) < ((*spaceship).x)){
			(*alien).x = (*alien).x+64;
		} else if(((*alien).x) > ((*spaceship).x)){
			(*alien).x = (*alien).x-64;
		}

		if((*alien).x > 128*190) {
			(*alien).x = 0;
		} else if((*alien).x < 0){
			(*alien).x = 128*190;
		}

		if((*alien).y < (*spaceship).y){
			(*alien).y = (*alien).y+64;
		} else if((*alien).y > (*spaceship).y){
			(*alien).y = (*alien).y-64;
		}

		if((*alien).y > 128*190) {
			(*alien).y = 0;
		} else if((*alien).y < 0){
			(*alien).y = 128*190;
		}

	}
}

int8_t shipAlienCollision(spaceship_t * spaceship, alien_t * alien){
 	int32_t alienXMax = (*alien).x+128;
 	int32_t alienXMin = (*alien).x-128;
 	int32_t alienYMax = (*alien).y+128;
 	int32_t alienYMin = (*alien).y-128;
	int32_t withinX = ((*spaceship).x <  alienXMax) && ((*spaceship).x >  alienXMin);
	int32_t withinY = ((*spaceship).y <  alienYMax) && ((*spaceship).y >  alienYMin);
	if(withinX && withinY && ((*alien).active)){
		(*alien).active = 0;
		return 1;
	} else {
		return 0;
	}
}

int8_t bulletAlienCollision(bullet_t * bullet, alien_t * alien, spaceship_t * spaceship){
	if((*bullet).active){
		int32_t alienXMax = (*alien).x+128;
		int32_t alienXMin = (*alien).x-128;
		int32_t alienYMax = (*alien).y+128;
		int32_t alienYMin = (*alien).y-128;
		int32_t withinX = ((*bullet).positionX <  alienXMax) && ((*bullet).positionX >  alienXMin);
		int32_t withinY = ((*bullet).positionY <  alienYMax) && ((*bullet).positionY >  alienYMin);
		if(withinX && withinY && ((*alien).active)){
			(*alien).active = 0;
			if(!(*spaceship).stoppingPower){
				(*bullet).active = 0;
			}
			return 1;
		} else {
			return 0;
		}
	}
}

void pickupPowerup(spaceship_t * spaceship, powerup_t * powerup, uint32_t lives){
	if((*powerup).active){
		if((*spaceship).x < (*powerup).x+256 && (*spaceship).x > (*powerup).x-256 && (*spaceship).y < (*powerup).y+256 && (*spaceship).y > (*powerup).y-256){
			if((*powerup).type == 1 && !((*spaceship).stoppingPower)){
				(*spaceship).stoppingPower = 1;
				(*powerup).type++;
				(*powerup).active = 0;
			} else if((*powerup).type == 2 && !((*spaceship).infiniteRange)){
				(*spaceship).infiniteRange = 1;
				(*powerup).type++;
				(*powerup).active = 0;
			} else {
				(*powerup).active = 0;
				lives++;
			}
		}
	}
}
