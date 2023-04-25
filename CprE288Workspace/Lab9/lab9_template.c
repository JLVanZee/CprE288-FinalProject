/**
 * @file lab9_template.c
 * @author
 * Template file for CprE 288 Lab 9
 */

#include "Timer.h"
#include "lcd.h"
#include "ping.h"
#include "open_interface.h"
#include "uart.h"
#include "cyBot_Scan.h"

// Uncomment or add any include directives that are needed

#warning "Possible unimplemented functions"
#define REPLACEME 0

int main(void) {
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();
//	oi_t *sensor_data = oi_alloc();
//	oi_init(sensor_data);
//	oi_free(sensor_data);

	ping_init();
	uart_init();
	cyBOT_init_Scan(0b0111);
    cyBOT_Scan_t scanner;

    right_calibration_value = 285250; //CyBot 12 calibration
    left_calibration_value = 1256500;

    cyBOT_Scan(90, &scanner); //Angles the ping sensor to 90 degrees for convenience


	float distance;
	uint8_t totalOverflow;
	char buffer;



	// YOUR CODE HERE


	while(1)
	{
      // YOUR CODE HERE
	    //buffer = uart_receive();
	    timer_waitMillis(500);
	    distance = ping_getDistance();
	    totalOverflow = get_totalOverflow();
	    lcd_printf("Distance: %.2f\nOverflow: %d", distance, totalOverflow);
	}

}
