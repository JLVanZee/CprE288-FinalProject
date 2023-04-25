///*
// * movement.c
// *
// *  Created on: Jan 31, 2023
// *
// */
//
//#include "open_interface.h"
//
//
///*
// * Returns 0 if it was able to reach its destination successfully without bumping into anything
// * Stops moving and returns -1 if there was a detection from the left bump sensor
// * Stops moving and returns 1 if there was a detection from the right bump sensor
// */
//int move_forward (oi_t *sensor_data, double distance_mm){
//    double sum = 0;
//
//    if (distance_mm < 0) {
//        distance_mm += (2*distance_mm);
//    }
//
//    oi_setWheels(300, 300);
//    oi_init(sensor_data);
//        while (sum < distance_mm) {
//            oi_update(sensor_data);
//            sum+= sensor_data->distance;
//            if (sensor_data->bumpLeft) {
//                return -1;
//            } else if (sensor_data->bumpRight) {
//                return 1;
//            }
//        }
//    oi_setWheels(0,0);
//    return 0;
//}
//
///*
// * turn_angle must be a positive value for the bot to turn left
// */
//void turn_left(oi_t *sensor_data) {
//   double angle = 0.0;
//   double turn_angle = 90.0;
//
//    oi_setWheels(50, -50);
//    while (angle < turn_angle) {
//        oi_update(sensor_data);
//        angle+= sensor_data->angle;
//    }
//    oi_setWheels(0,0);
//}
//
///*
// * turn_angle must be a negative value for the bot to turn right
// */
//void turn_right(oi_t *sensor_data) {
//   double angle = 0.0;
//   double turn_angle = -90.0;
//
//    oi_setWheels(-50, 50);
//    while (angle > turn_angle) {
//        oi_update(sensor_data);
//        angle+= sensor_data->angle;
//    }
//    oi_setWheels(0,0);
//}
//
///**
// * The distance given must be negative when used in the function. Though this function
// * has been built so that it can receive either a positive or negative value. In case of
// * receiving a positive value, it will make the value negative before working with it
// */
//void move_backward(oi_t *sensor_data, double distance_mm){
//    double sum = 0;
//    if (distance_mm > 0) {
//        distance_mm -= (distance_mm*2);
//    }
//
//    oi_setWheels(-300, -300);
//    oi_init(sensor_data);
//        while (sum > distance_mm) {
//            oi_update(sensor_data);
//            sum+= sensor_data->distance;
//        }
//    oi_setWheels(0,0);
//}
//
///*
// * turn_angle must be a positive value for the bot to turn left
// * Either a positive or a negative value will work, the value
// * will be converted to the correct value beforehand if needed
// */
//void turn_degrees_left(oi_t *sensor_data, double turn_angle) {
//   double angle = 0.0;
//
//   if (turn_angle < 0) {
//       turn_angle += (2*turn_angle);
//   }
//
//    oi_setWheels(50, -50);
//    while (angle < turn_angle) {
//        oi_update(sensor_data);
//        angle+= sensor_data->angle;
//    }
//    oi_setWheels(0,0);
//}
//
///*
// * turn_angle must be a negative value for the bot to turn right
// * Either a positive or a negative value will work, the value
// * will be converted to the correct value beforehand if needed
// */
//void turn_degrees_right(oi_t *sensor_data, double turn_angle) {
//   double angle = 0.0;
//   if (turn_angle > 0) {
//       turn_angle -= (turn_angle*2);
//   }
//
//    oi_setWheels(-50, 50);
//    while (angle > turn_angle) {
//        oi_update(sensor_data);
//        angle+= sensor_data->angle;
//    }
//    oi_setWheels(0,0);
//}
//
//
//
//
