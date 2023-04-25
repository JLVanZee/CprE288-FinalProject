/// Simple 'Hello, world' program
/**
 * This program prints "Hello, world" to the LCD screen
 * @author Chad Nelson
 * @date 06/26/2012
 *
 * updated: phjones 9/3/2019
 * Description: Added timer_init call, and including Timer.h
 */

#include "Timer.h"
#include "lcd.h"
#include <string.h>

//lcd_rotatingBanner(char[] message);

int main (void) {

 	//timer_init(); // Initialize Timer, needed before any LCD screen functions can be called
	              // and enables time functions (e.g. timer_waitMillis)

	//lcd_init();   // Initialize the LCD screen.  This also clears the screen.



	lcd_rotatingBanner();
	// lcd_puts("Hello, world"); // Replace lcd_printf with lcd_puts
        // step through in debug mode and explain to TA how it works
    
	// NOTE: It is recommended that you use only lcd_init(), lcd_printf(), lcd_putc, and lcd_puts from lcd.h.
       // NOTE: For time functions, see Timer.h

	return 0;
}

void lcd_rotatingBanner() {
    char message[] = "                    Microcontrollers are lots of fun!                   "; //
    char display[20];
    char clear[21] = "                    ";
    int i, k = 0;

    lcd_init();
    timer_init();

    int lowerLim = 0;
    int upperLim = 19;

    while (1) {
        for (i = lowerLim; i < upperLim; ++i) {
            display[k] = message[i];
            ++k;
        }
        k = 0;
        ++lowerLim;
        ++upperLim;

        lcd_printf(display);

        if(upperLim == strlen(message)) {
            lowerLim = 0;
            upperLim = 19;
        }

        timer_waitMillis(300);
        lcd_printf(clear);
        display[0] = '\0';

    }
}
