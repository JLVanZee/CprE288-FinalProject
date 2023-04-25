/*
 * movement.h
 *
 *  Created on: Jan 31, 2023
 *      Author: aqsutton
 */

#ifndef MOVEMENT_H_
#define MOVEMENT_H_

    void move_forward (oi_t *sensor_data, double distance_mm);

    void draw_square(oi_t *sensor_data);

    void turn_left(oi_t *sensor_data);

    void turn_right(oi_t *sensor_data);

    void move_backward (oi_t *sensor_data, double distance_mm);


#endif /* MOVEMENT_H_ */
