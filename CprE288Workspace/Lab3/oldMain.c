#include "cyBot_uart.h"
#include "lcd.h"
#include "open_interface.h"
#include <string.h>
#include "movement.h"
#include "cyBot_scan.h"

/**
 * main.c
 */

void stringReturn(char* returnString);

typedef struct {
    int angle;
    float distance;
} scanData;

int main(void)
{
    lcd_init();
    cyBot_uart_init();
    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);
    cyBOT_init_Scan(0b0111);
        right_calibration_value = 290500; //CyBot 0 calibration
        left_calibration_value = 1256500;


    char var = (char) cyBot_getByte();
    char string[100] = "";
    scanData scan[91];

        if (var == 'm') {
            int i;
            char string[100] = "";
            int counter = 0;
            cyBOT_Scan_t scanner;

            //stringReturn("Angle    Distance (cm)\r\n");
            for (i = 0; i <= 180; i += 2) {
                cyBOT_Scan(i, &scanner);
                //sprintf(string, "%d        %.2f\r\n", i, scanner.sound_dist);
                scan[counter].angle = i;
                scan[counter].distance = scanner.sound_dist;

                //stringReturn(string);
                ++counter;
            }

    //        for (i = 0; i < 91; ++i) {    //FOR TESTING ARRAY CONTENT
    //            printf("%d  %.2f\n", scan[i].angle, scan[i].distance);
    //        }

            int currentLength = 0;

            int smallLength = 999;
            int smallAngle;
            scanData object[91];
            int count = 0;

            stringReturn("Raw Values:\r\n");
            for (i = 0; i < 91; ++i) {
                if (scan[i].distance < 45.0) {
                        object[count] = scan[i];
                        sprintf(string, "\r\n%d    %.2f", object[count].angle, object[count].distance);
                        stringReturn(string);
                        ++count;
                }
            }

            stringReturn("\r\n");
            stringReturn("\r\n");
            stringReturn("Objects:\r\n");
            int j;
            for (i = 0; i < count-2; ++i) {
                if (abs(object[i].distance - object[i+1].distance) < 1.5) {
                    currentLength += 1;
                    sprintf(string, "Angle: %d, Distance: %.2f\r\n", object[i].angle, object[i].distance);
                    stringReturn(string);
                    ;
                    //stringReturn("\r\n");
                } else {
                    if (currentLength < smallLength && currentLength >= 3) {
                        smallLength = currentLength;
//                        for (j = i; j >= i-currentLength; --j) {
//                            sprintf(string, "Angle: %d, Distance: %.2f\r\n", object[j].angle, object[j].distance);
//                            stringReturn(string);
//                        }

                        smallAngle = (object[i].angle + object[i-currentLength].angle) / 2;
                    }
                    currentLength = 0;
                    stringReturn("\r\n");
                }
            }

            cyBOT_Scan(smallAngle, &scanner);

        }




//    while(1) {
//            char var = (char) cyBot_getByte();
//            char string[100] = "";
//
//            sprintf(string, "got a %c", var);
//            lcd_putc(var);
//            if (var == 'w') {
//                move_forward(sensor_data, 100);
//            } else if (var == 'a') {
//                turn_left(sensor_data);
//            } else if (var == 's') {
//                move_backward(sensor_data, 100);
//            } else if (var == 'd') {
//                turn_right(sensor_data);
//            } else if (var == 'x') {
//                break;
//            }
//    }
//    cyBot_sendByte(string);
//    stringReturn(string);

    //lcd_putc();
    oi_free(sensor_data);

    return 0;
}

scanData* scanRange(int beginning, int end) {
    int i;
    char string[100] = "";
    scanData scan[91];
    int counter = 0;
    cyBOT_Scan_t scanner;
    for (i = 0; i <= 180; i += 2) {
        cyBOT_Scan(i, &scanner);
        sprintf(string, "%d        %.2f\r\n", i, scanner.sound_dist);
        scan[counter].angle = i;
        scan[counter].distance = scanner.sound_dist;
        stringReturn(string);
        ++counter;
    }

    return scan;
}


void stringReturn(char* returnString) {
    int i = 0;
    for (i = 0; i < strlen(returnString); ++i) {
        cyBot_sendByte(returnString[i]);
    }

}
