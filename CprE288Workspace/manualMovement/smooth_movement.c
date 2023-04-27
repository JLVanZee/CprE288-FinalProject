/*
 * movement.c
 *
 *  Created on: Jan 31, 2023
 *
 */

#include "open_interface.h"
#include "uart.h"


/*
 * Returns 0 if it was able to reach its destination successfully without bumping into anything
 * Stops moving and returns -1 if there was a detection from the left bump sensor
 * Stops moving and returns 1 if there was a detection from the right bump sensor
 */
int move_forward (oi_t *sensor_data, char drive){
    double sum = 0;

    oi_setWheels(300, 300);
    oi_init(sensor_data);
        while (drive == 'w') {
            oi_update(sensor_data);
            sum+= sensor_data->distance;
            drive = uart_receive_nonblocking();

            if(sensor_data -> bumpRight){
                uart_sendStr("Bump Right");
                break;
            }
            if(sensor_data -> bumpLeft){
                uart_sendStr("Bump Left");
                break;
            }
            if(sensor_data -> cliffLeftSignal < 2300 || sensor_data -> cliffFrontLeftSignal < 2300){
                uart_sendStr("CAUTION LEFT PIT");
                break;
            }
            if(sensor_data -> cliffRightSignal < 2300 || sensor_data -> cliffFrontRightSignal < 2300){
                uart_sendStr("CAUTION RIGHT PIT");
                break;
            }
            if(sensor_data -> cliffLeftSignal > 2700 || sensor_data -> cliffFrontLeftSignal > 2700){
                uart_sendStr("LEFT SENSOR ON BOUNDARY");
                break;
            }
            if(sensor_data -> cliffRightSignal > 2700 || sensor_data -> cliffFrontRightSignal > 2700){
                uart_sendStr("RIGHT SENSOR ON BOUNDARY");
                break;
            }

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

/**
 * The distance given must be negative when used in the function. Though this function
 * has been built so that it can receive either a positive or negative value. In case of
 * receiving a positive value, it will make the value negative before working with it
 */
void move_backward(oi_t *sensor_data, char drive){
    double sum = 0;

    oi_setWheels(-300, -300);
    oi_init(sensor_data);
        while (drive == 's') {
            oi_update(sensor_data);
            sum+= sensor_data->distance;
            drive = uart_receive_nonblocking();
        }
    oi_setWheels(0,0);
}

/*
 * turn_angle must be a positive value for the bot to turn left
 * Either a positive or a negative value will work, the value
 * will be converted to the correct value beforehand if needed
 */
void turn_degrees_left(oi_t *sensor_data, char drive) {
   double angle = 0.0;



    oi_setWheels(50, -50);
    while (drive == 'q') {
        oi_update(sensor_data);
        angle+= sensor_data->angle;
        drive = uart_receive_nonblocking();
    }
    oi_setWheels(0,0);
}

/*
 * turn_angle must be a negative value for the bot to turn right
 * Either a positive or a negative value will work, the value
 * will be converted to the correct value beforehand if needed
 */
void turn_degrees_right(oi_t *sensor_data, char drive) {
   double angle = 0.0;


    oi_setWheels(-50, 50);
    while (drive == 'e') {
        oi_update(sensor_data);
        angle+= sensor_data->angle;
        drive = uart_receive_nonblocking();
    }
    oi_setWheels(0,0);
}




