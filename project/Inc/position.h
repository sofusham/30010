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
int8_t asteroidBulletCollision(asteroid_t * asteroid, bullet_t * bullet);


#endif /* POSITION_H_ */
