/*
 * ball.h
 *
 *  Created on: 12. jun. 2023
 *      Author: sofus
 */

#ifndef BALL_H_
#define BALL_H_

typedef struct {
	int32_t x, y, rotation, velX, velY;
} ball_t ;

void update_spaceship(ball_t * ball_p, int dir);
void draw_new_spaceship(ball_t * ball_p, int32_t tempX, int32_t tempY, int8_t tempR);
void wind_resistance(ball_t * ball_p);
void update_velocity(ball_t * ball_p);

#endif /* BALL_H_ */
