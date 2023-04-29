

#include "Timer.h"
#include "lcd.h"
#include "open_interface.h"
#include "servo.h"
#include "button.h"
#include "GUI.h"


int main(void) {
    servo_init();
    timer_init(); // Must be called before lcd_init(), which uses timer functions
    lcd_init();
    button_init();

//    oi_t *sensor_data = oi_alloc();
//    oi_init(sensor_data);
//    oi_free(sensor_data);
//
//    servo_move(0);
//    timer_waitMillis(4000);
//
//
//
//    servo_move(180);
//    timer_waitMillis(4000);
//
//    servo_move(90);

    GUI_init();

    build_control_interface();

    build_data_interface();


//    int pos = 0, current_angle = 0;
//    while(pos != 0b1000) {
//        pos = button_getButton();
//
//
//        if (pos == 0b00000001) { //button 1
////           if (current_angle + 1 > 180) {
////               continue;
////           } else {
////               current_angle += 1;
////               servo_move(current_angle);
////               timer_waitMillis(4);
////           }
//
//           if (current_angle + 1 <= 180) {
//               current_angle += 1;
//               servo_move(current_angle);
//               timer_waitMillis(4);
//           }
//        } else if (pos == 0b00000010) { //button 2
////            if (current_angle - 1 < 0) {
////               continue;
////           } else {
////               current_angle -= 1;
////               servo_move(current_angle);
////               timer_waitMillis(4);
////           }
//
//            if (current_angle - 1 >= 0) {
//                current_angle -= 1;
//                servo_move(current_angle);
//                timer_waitMillis(4);
//            }
//        }
//    }


    return 0;
}
