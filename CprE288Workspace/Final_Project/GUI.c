


#include "uart.h"




void GUI_init() {
    uart_init();
    uart_sendStr("THIS GUI DISPLAYS CONTROLS FOR ALL BUTTONS THAT FUNCTION AS INPUTS\r\n");
    uart_sendStr("THE GUI WILL ALSO DISPLAY DATA FROM THE TEST FIELD, THIS DATA INCLUDES:\r\n");
    uart_sendStr("  1. Objects detected from a scan\r\n");
    uart_sendStr("  2. The total distance the CyBot has moved forward or backward\r\n");
    uart_sendStr("  3. Shows that the CyBot has been instructed to turn left or right and indicates when it has completed its movement\r\n");
    uart_sendStr("  4. The amount of degrees turned either left or right\r\n");
    uart_sendStr("  5. Functional interrupts when either a cliff or bump sensor is triggered,\r\n");
    uart_sendStr("     sending the GUI into a busy wait forcing the user to acknowledge the sensor reading\r\n");
    uart_sendStr("  6. Forced acknowledgments when a sensor is triggered, giving control back to the user\r\n\r\n");
    uart_sendStr("TEAM MEMBERS INCLUDE: JARET VAN ZEE, ALEC SUTTON, EVERETT DUFFY, and ZANE LENZ\r\n\r\n");
}


void build_control_interface() {
    uart_sendStr("****************************************************************************************************\r\n");
    uart_sendStr("*                                 PRESS 'w' TO MOVE FORWARD                                        *\r\n");
    uart_sendStr("*  PRESS 'a' TO TURN LEFT         PRESS 's' TO MOVE BACKWARDS            PRESS 'd' TO TURN RIGHT   *\r\n");
    uart_sendStr("*                                                                                                  *\r\n");
    uart_sendStr("*  PRESS 'q' TO TURN A SPECIFIC AMOUNT OF DEGREES LEFT                                             *\r\n");
    uart_sendStr("*  PRESS 'e' TO TURN A SPECIFIC AMOUNT OF DEGREES RIGHT                                            *\r\n");
    uart_sendStr("*                                                                                                  *\r\n");
    uart_sendStr("*  PRESS 'g' TO START A SCAN PROCESS, SCANNING FROM 0 TO 180 DEGREES                               *\r\n");
    uart_sendStr("*  PRESS 'i' TO ACKNOWLEDGE A FORCED INTERRUPT                                                     *\r\n");
    uart_sendStr("*  PRESS 'p' TO DISPLAY THE INSTRUCTIONS AGAIN                                                     *\r\n");
    uart_sendStr("*                                                                                                  *\r\n");
    uart_sendStr("*                                                                                                  *\r\n");
    uart_sendStr("*  POSSIBLE TROUBLESHOOTING GUIDE:                                                                 *\r\n");
    uart_sendStr("*    1. ENSURE CAPS LOCK IS OFF                                                                    *\r\n");
    uart_sendStr("*    2. ENSURE THE CYBOT IS TURNED ON                                                              *\r\n");
    uart_sendStr("*                                                                                                  *\r\n");
    uart_sendStr("****************************************************************************************************\r\n\r\n");
    uart_sendStr("DATA FROM CYBOT WILL APPEAR BELOW THIS LINE:\r\n");
}

void build_data_interface() {

}
