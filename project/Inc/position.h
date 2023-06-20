/*
 * position.h
 *
 *  Created on: 14 Jun 2023
 *      Author: moebe
 */

#ifndef POSITION_H_
#define POSITION_H_

void calculateNextAst( asteroid_t * asteroid);
void calculateNextShip( spaceship_t * spaceship);
void updatePosAst( asteroid_t * asteroid);
void updatePosShip( spaceship_t * spaceship);
int8_t shipAsteroidCollision(spaceship_t * spaceship, asteroid_t * asteroid );
int8_t asteroidBulletCollision(asteroid_t * asteroid, bullet_t * bullet, spaceship_t * spaceship);
void moveAlien(alien_t * alien, spaceship_t * spaceship);
int8_t shipAlienCollision(spaceship_t * spaceship, alien_t * alien);
int8_t bulletAlienCollision(bullet_t * bullet, alien_t * alien, spaceship_t * spaceship);
void pickupPowerup(spaceship_t * spaceship, powerup_t * powerup, uint32_t lives);



#endif /* POSITION_H_ */
