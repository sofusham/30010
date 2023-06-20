/*
 * spaceship.h
 *
 *  Created on: 12. jun. 2023
 *      Author: sofus
 */

#ifndef spaceship_H_
#define spaceship_H_

typedef struct {
	int32_t x, y, rotation, velX, velY, nextPosX, nextPosY;
	int8_t infiniteRange, stoppingPower;
} spaceship_t ;

void do_the_thing(spaceship_t * spaceship_p, int16_t *prevRot, int16_t *curRot);
void update_spaceship(spaceship_t * spaceship_p, int16_t *prevRot, int16_t *curRot);
void draw_new_spaceship(spaceship_t * spaceship_p, int32_t tempX, int32_t tempY, int8_t tempR);
void wind_resistance(spaceship_t * spaceship_p);
void update_velocity(spaceship_t * spaceship_p);
void wrapping(spaceship_t * spaceship_p);

#endif /* spaceship_H_ */
