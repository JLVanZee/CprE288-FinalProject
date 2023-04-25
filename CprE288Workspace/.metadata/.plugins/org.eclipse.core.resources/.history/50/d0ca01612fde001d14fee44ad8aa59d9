/**
 * lab6-interrupt_template.c
 *
 * Template file for CprE 288 Lab 6
 *
 * @author Diane Rover, 2/15/2020
 *
 */

#include "Timer.h"
#include "lcd.h"
#include "cyBot_Scan.h"  // For scan sensors
#include <stdbool.h>
#include "open_interface.h"
#include "movement.h"


typedef struct {
    int angle;
    int IR_value;
    float distance;
} scanData;

typedef struct {
    int angle;
    double radialWidth;
    double distance;
} object;

int main(void) {



    timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();
    cyBOT_init_Scan(0b0111);
    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);
    uart_init();
    cyBOT_init_Scan(0b0111);

    right_calibration_value = 285250; //CyBot 0 calibration
    left_calibration_value = 1214500;

    cyBOT_Scan_t scanner;
    scanData scan[91];
    char sendString[100];

    object detectedObjects[15]; //Number 15 can be changed, this is assumed the maximum amount of objects on the field at one time



    char begin = uart_receive();

    if (begin != 'm') {
        oi_free(sensor_data);
        exit(0);
    }


    move_forward(&sensor_data, 600);
    turn_left(&sensor_data);
    move_forward(&sensor_data, 600);
    turn_right(&sensor_data);
    move_forward(&sensor_data, 600);





	oi_free(sensor_data);

	return 0;
}
