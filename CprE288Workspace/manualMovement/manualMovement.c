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
#include <stdbool.h>
#include "open_interface.h"
#include "smooth_movement.h"
#include "uart.h"



int main(void) {



    timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();
    cyBOT_init_Scan(0b0111);
    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);
    uart_init();
    cyBOT_init_Scan(0b0111);


    char sendString[100];


    char movementDirection;
    int check = 1;

    while (check) {
        movementDirection = uart_receive_nonblocking();

        switch(movementDirection) {
            case 'w':
                move_forward(sensor_data, movementDirection);
                break;
            case 's':
                move_backward(sensor_data, movementDirection);
                break;
            case 'a':
                turn_left(sensor_data);
                break;
            case 'd':
                turn_right(sensor_data);
                break;
            case 'q':
                turn_degrees_left(sensor_data, movementDirection);
                break;
            case 'e':
                turn_degrees_right(sensor_data, movementDirection);
                break;
            case 'f':
                check = 0;
                break;
       }
   }





	oi_free(sensor_data);

	return 0;
}
