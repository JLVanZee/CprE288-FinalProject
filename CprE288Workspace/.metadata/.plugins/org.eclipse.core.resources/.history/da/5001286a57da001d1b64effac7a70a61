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


    int i, j;
    int counter = 0;


    while(1) {
        uart_sendStr("RAW VALUES\r\n");

        for (i = 0; i <= 180; i += 2) {
            cyBOT_Scan(i, &scanner);
            scan[counter].angle = i;
            scan[counter].IR_value = scanner.IR_raw_val;
            scan[counter].distance = scanner.sound_dist;

            for (j = 1; j < 2; ++j) {
                cyBOT_Scan(i, &scanner);
                scan[counter].IR_value += scanner.IR_raw_val;
            }

            scan[counter].IR_value /= 3;

            sprintf(sendString, "Angle: %d  Distance: %.2f  IR Value Avg: %d\r\n", scan[counter].angle, scan[counter].distance, scan[counter].IR_value);
            uart_sendStr(sendString);
            ++counter;
        } //IR RANGE 750 - 1700

        //Increments to keep track of the length of a detected object
        int objectLength = 0;

        //First and last index of detected object in array
        int firstIndex, lastIndex;

        //Chord length calculation variables
        int angle;
        double radius, radialWidth;

        //Index for the detected objects array
        int index = 0;

        uart_sendStr("\r\n\r\n");
        uart_sendStr("Detected Object\r\n");

        for (i = 0; i < 89; ++i) {
            if (scan[i].IR_value >= 620 && scan[i].IR_value <= 1700) {
                if (abs(scan[i].IR_value - scan[i+1].IR_value) <= 100) {
                    objectLength += 1;

                    sprintf(sendString, "Angle: %d  Distance: %.2f  IR Value Avg: %d\r\n", scan[i].angle, scan[i].distance, scan[i].IR_value);
                    uart_sendStr(sendString);

                    continue;
                }
            }

            if (objectLength >= 2) {
                lastIndex = i+1;
                firstIndex = i-objectLength;
                uart_sendStr("\r\n");

                detectedObjects[index].distance = (scan[firstIndex].distance + scan[lastIndex].distance) / 2;
                detectedObjects[index].angle = (scan[lastIndex].angle + scan[firstIndex].angle) / 2;

                detectedObjects[index].radialWidth = 2.0 * detectedObjects[index].distance * sin( (3.1415926535 / 180) * ((scan[lastIndex].angle - scan[firstIndex].angle) / 2) );

                index += 1;
            }

            objectLength = 0;
        }


        //This section goes finds the smallest object in the list of detected objects
        int smallIndex;
        double smallWidth = 999.0;

        uart_sendStr("\r\nDetected Objects\r\n");

        for (i = 0; i < index; ++i) {
            sprintf(sendString, "Object %d: Radial Width - %.2lf  Angle - %d  Distance - %.2lf\r\n", i, detectedObjects[i].radialWidth, detectedObjects[i].angle, detectedObjects[i].distance);
            uart_sendStr(sendString);

            if (detectedObjects[i].radialWidth < smallWidth) {
                smallIndex = i;
                smallWidth = detectedObjects[i].radialWidth;
            }
        }

        //cyBOT_Scan(detectedObjects[smallIndex].angle, &scanner); //Moves scanner initially to smallest object


        double turn_angle = detectedObjects[smallIndex].angle - 90.0;
        int forward_movement = ((int)detectedObjects[smallIndex].distance * 10) - 150; //converts the distance value from cm to mm, then takes off 50 mm / 5 cm
        if (turn_angle >= 0.0) {
            turn_degrees_left(&sensor_data, turn_angle);
        } else {
            turn_degrees_right(&sensor_data, turn_angle);
        }

        int objectDetection = move_forward(&sensor_data, forward_movement);


        if (objectDetection != 0) {
            move_backward(&sensor_data, -100);
            if (turn_angle >= 0) {
                turn_left(&sensor_data);
                move_forward(&sensor_data, 180);
                turn_right(&sensor_data);
            } else {
                turn_right(&sensor_data);
                move_forward(&sensor_data, 180);
                turn_left(&sensor_data);
            }
            continue;
        }
        break;
    }


    //char begin = uart_receive();


    //move_backward(&sensor_data, -500);


	oi_free(sensor_data);

	return 0;
}
