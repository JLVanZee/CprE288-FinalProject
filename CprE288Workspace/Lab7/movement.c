/*
 * movement.c
 *
 *  Created on: Jan 31, 2023
 *      Author: aqsutton
 */

#include "open_interface.h"


/*
 * Returns 0 if it was able to reach its destination successfully without bumping into anything
 * Stops moving and returns -1 if there was a detection from the left bump sensor
 * Stops moving and returns 1 if there was a detection from the right bump sensor
 */
int move_forward (oi_t *sensor_data, double distance_mm){
    double sum = 0;

    oi_setWheels(300, 300);
    oi_init(sensor_data);
        while (sum < distance_mm) {
            oi_update(sensor_data);
            sum+= sensor_data->distance;
            if (sensor_data->bumpLeft) {
                return -1;
            } else if (sensor_data->bumpRight) {
                return 1;
            }

//            if (sensor_data->bumpLeft || sensor_data->bumpRight) {
//                oi_setWheels(0, 0);
//                move_backward(sensor_data, -150);
//
//                if (sensor_data->bumpLeft) {
//                    move_backward(sensor_data, -150);
//                    turn_right(sensor_data);
//                    move_forward(sensor_data, 250);
//                    turn_left(sensor_data);
//                } else if (sensor_data->bumpRight) {
//                    move_backward(sensor_data, -150);
//                    turn_left(sensor_data);
//                    move_forward(sensor_data, 250);
//                    turn_right(sensor_data);
//                }
//
//                oi_setWheels(300, 300);
//            }

        }
    oi_setWheels(0,0);
    return 0;
}

/*
 * turn_angle must be a positive value for the bot to turn left
 */
void turn_left(oi_t *sensor_data) {
   double angle = 0.0;
   double turn_angle = 90.0;

    oi_setWheels(50, -50);
    while (angle < turn_angle) {
        oi_update(sensor_data);
        angle+= sensor_data->angle;
    }
    oi_setWheels(0,0);
}

/*
 * turn_angle must be a negative value for the bot to turn right
 */
void turn_right(oi_t *sensor_data) {
   double angle = 0.0;
   double turn_angle = -90.0;

    oi_setWheels(-50, 50);
    while (angle > turn_angle) {
        oi_update(sensor_data);
        angle+= sensor_data->angle;
    }
    oi_setWheels(0,0);
}

void move_backward(oi_t *sensor_data, double distance_mm){
    double sum = 0;

    oi_setWheels(-300, -300);
    oi_init(sensor_data);
        while (sum > distance_mm) {
            oi_update(sensor_data);
            sum+= sensor_data->distance;
        }
    oi_setWheels(0,0);
}

/*
 * turn_angle must be a positive value for the bot to turn left
 */
void turn_degrees_left(oi_t *sensor_data, double turn_angle) {
   double angle = 0.0;

    oi_setWheels(50, -50);
    while (angle < turn_angle) {
        oi_update(sensor_data);
        angle+= sensor_data->angle;
    }
    oi_setWheels(0,0);
}

/*
 * turn_angle must be a negative value for the bot to turn right
 */
void turn_degrees_right(oi_t *sensor_data, double turn_angle) {
   double angle = 0.0;

    oi_setWheels(-50, 50);
    while (angle > turn_angle) {
        oi_update(sensor_data);
        angle+= sensor_data->angle;
    }
    oi_setWheels(0,0);
}


//void bump(oi_t *sensor_data)
