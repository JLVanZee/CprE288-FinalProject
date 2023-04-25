/**
 * Driver for ping sensor
 * @file ping.c
 * @author
 */

#include "servo.h"
#include "Timer.h"
#include "open_interface.h"

void servo_init(void) {
    SYSCTL_RCGCGPIO_R |= 0x02; //Enables GPIO PORT B
    SYSCTL_RCGCTIMER_R |= 0x02; //Enables TIMER Clock
    while ((SYSCTL_PRGPIO_R & 0x02) == 0) {}; //Waits until GPIO PORT B is ready
    while ((SYSCTL_PRTIMER_R & 0x02) == 0) {};

    GPIO_PORTB_AFSEL_R |= 0x20;
    GPIO_PORTB_PCTL_R |= 0x700000;
    GPIO_PORTB_DEN_R |= 0x20;

    TIMER1_CTL_R &= ~0x100; // Disables the timer to modify it
    TIMER1_CTL_R &= ~0x4000;

    TIMER1_CFG_R |= 0x4;

    TIMER1_TBMR_R = 0xA;

    TIMER1_TBILR_R = 0x4E200 & 0xFFFF;
    TIMER1_TBPR_R = 0x4E200 >> 16;

    TIMER1_TBMATCHR_R = 0x4BED8;
    TIMER1_TBPMR_R = 0x4BED8 >> 16;

    TIMER1_CTL_R |= 0x100;


}

void servo_move(uint16_t degrees) {
    float seconds = (degrees * (1 / 180.0)) * 27000;
    uint32_t periods = 320000 - 9000 - seconds;

    TIMER1_TBMATCHR_R = periods & 0xFFFF;
    TIMER1_TBPMR_R = periods >> 16;
}
