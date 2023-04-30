/*
 * servo.h
 *
 *  Created on: Apr 10, 2023
 *      Author: jlvanzee
 */

#ifndef SERVO_H_
#define SERVO_H_

#include "Timer.h"

void servo_init(void);

void servo_move(uint16_t degrees);

#endif /* SERVO_H_ */
