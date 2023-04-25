///**
// * lab6_template.c
// *
// * Template file for CprE 288 Lab 6
// *
// * @author Diane Rover, 2/15/2020
// *
// */
//
//#include "Timer.h"
//#include "lcd.h"
//#include "cyBot_Scan.h"  // For scan sensors
//#include "uart.h"
//#include "open_interface.h"
//
//
//// Uncomment or add any include directives that are needed
//// #include "open_interface.h"
//// #include "movement.h"
//// #include "button.h"
//
//
//#warning "Possible unimplemented functions"
//#define REPLACEME 0
//
//
//int main(void) {
//	timer_init(); // Must be called before lcd_init(), which uses timer functions
//	lcd_init();
//	uart_init();
//    //cyBOT_init_Scan();
//
//	oi_t *sensor_data = oi_alloc();
//	oi_init(sensor_data);
//
//    cyBOT_init_Scan(0b0111);
//    right_calibration_value = 290500; //CyBot 0 calibration
//    left_calibration_value = 1256500;
//
//
//
//	// YOUR CODE HERE
//
//
//    int i = 0;
//    char test;
//	while(1)
//	{
//	    test = uart_receive_nonblocking();
//
//	    if (test == 's') break;
//
//	    cyBOT_Scan(i, sensor_data);
//	    i += 2;
//	    if (i > 180) i=0;
//
//
//	}
//
//}
