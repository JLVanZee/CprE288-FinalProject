/**
 * lab4_template.c
 *
 * Template file for CprE 288 lab 4
 *
 * @author Zhao Zhang, Chad Nelson, Zachary Glanz
 * @date 08/14/2016
 */

#include "button.h"
#include <stdint.h>
#include "Timer.h"
#include "open_interface.h"
#include "lcd.h"
#include "cyBot_uart.h"  // Functions for communicating between CyBot and Putty (via UART)
                         // PuTTy: Baud=115200, 8 data bits, No Flow Control, No Parity, COM1

//#warning "Possible unimplemented functions"
#define REPLACEME 0



int main(void) {
	button_init();
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();
	cyBot_uart_init();
	            // Don't forget to initialize the cyBot UART before trying to use it

	// YOUR CODE HERE

	uint8_t pos;
	uint8_t previous;
	char string[100] = "";
	

	while(1)
	{
	    pos = button_getButton();

	    if (pos == previous) {
	        continue;
	    }
	    if (pos == 0b00000001) {
	        sprintf(string, "You pressed button 1\r\n");
	        stringReturn(string);
	    } else if (pos == 0b00000010) {
	        sprintf(string, "You pressed button 2\r\n");
	        stringReturn(string);
	    } else if (pos == 0b00000100) {
	        sprintf(string, "You pressed button 3\r\n");
	        stringReturn(string);
	    } else if (pos == 0b00001000) {
	        sprintf(string, "You pressed button 4\r\n");
	        stringReturn(string);
	    }
	    previous = pos;

	}

}

void stringReturn(char* returnString) {
    int i = 0;
    for (i = 0; i < strlen(returnString); ++i) {
        cyBot_sendByte(returnString[i]);
    }
}
