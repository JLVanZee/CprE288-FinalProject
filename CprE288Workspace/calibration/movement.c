/*
 * movement.c
 *
 *  Created on: Jan 31, 2023
 *      Author: aqsutton
 */

#include "open_interface.h"

void move_forward (oi_t *sensor_data, double distance_mm){
    double sum = 0;

    oi_setWheels(300, 300);
    oi_init(sensor_data);
        while (sum < distance_mm) {
            oi_update(sensor_data);
            sum+= sensor_data->distance;

            if (sensor_data->bumpLeft || sensor_data->bumpRight) {
                oi_setWheels(0, 0);
                move_backward(sensor_data, -150);

                if (sensor_data->bumpLeft) {
                    move_backward(sensor_data, -150);
                    turn_right(sensor_data);
                    move_forward(sensor_data, 250);
                    turn_left(sensor_data);
                } else if (sensor_data->bumpRight) {
                    move_backward(sensor_data, -150);
                    turn_left(sensor_data);
                    move_forward(sensor_data, 250);
                    turn_right(sensor_data);
                }

                oi_setWheels(300, 300);
            }

        }
    oi_setWheels(0,0);
}

//void draw_square(oi_t *sensor_data) {
//    double angle = 0.0;
//    double turn_angle = 90.0;
//    double sum = 0.0;
//    oi_init(sensor_data);
//
//    int i;
//    for (i = 0; i < 4; ++i) {
//        oi_setWheels(500, 500);
//
//        while (sum < 500) {
//            oi_update(sensor_data);
//            sum+= sensor_data->distance;
//
//        }
//        oi_setWheels(0,0);
//
//        oi_setWheels(50, -50);
//        while (angle < turn_angle) {
//            oi_update(sensor_data);
//            angle+= sensor_data->angle;
//        }
//        oi_setWheels(0,0);
//        turn_angle += 90.0;
//
//        sum = 0.0;
//    }
//}

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

void move_backward (oi_t *sensor_data, double distance_mm){
    double sum = 0;

    oi_setWheels(-300, -300);
    oi_init(sensor_data);
        while (sum > distance_mm) {
            oi_update(sensor_data);
            sum+= sensor_data->distance;
        }
    oi_setWheels(0,0);
}


//void bump(oi_t *sensor_data)
