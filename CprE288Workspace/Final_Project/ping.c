/**
 * Driver for ping sensor
 * @file ping.c
 * @author
 */

#include "ping.h"
#include "Timer.h"
#include "lcd.h"


volatile unsigned long START_TIME = 0;
volatile unsigned long END_TIME = 0;
volatile unsigned long TOTAL_TIME = 0;
volatile enum{LOW, HIGH, DONE} STATE = LOW; // State of ping echo pulse

uint8_t overflow_count = 0;

void ping_init (void){

  // YOUR CODE HERE
    SYSCTL_RCGCGPIO_R |= 0b000010;
    while ((SYSCTL_PRGPIO_R & 0x02) == 0) {};
    SYSCTL_RCGCTIMER_R |= 0x08; //Enables TIMER3 Clock

    GPIO_PORTB_AFSEL_R |= 0x8;
    GPIO_PORTB_PCTL_R |= 0x7000; //maybe clear with &=
    GPIO_PORTB_DEN_R |= 0x8;

    // Configure and enable the timer
    TIMER3_CTL_R &= ~0x100; //disables the timer so it can be configured
    TIMER3_CTL_R |= 0xC00; //configures the timer to detect both edges

    TIMER3_CFG_R |= 0x4;
    TIMER3_TBMR_R |= 0x7;
    TIMER3_TBMR_R &= ~0x10;
    TIMER3_TBPR_R |= 0xFF; // 8-bit addition
    TIMER3_TBILR_R |= 0xFFFF; // 16-bit count-down

    NVIC_EN1_R |= 0x10;
    NVIC_PRI9_R |= 0x20;
    //NVIC_PIR9_R &= ~0xC0;
    TIMER3_IMR_R |= 0x400; //Enabling capture time interrupt for timer B
    TIMER3_ICR_R |= 0x400; // Clears the possibility of an interrupt in timer B
    IntRegister(INT_TIMER3B, TIMER3B_Handler);

    IntMasterEnable();

    TIMER3_CTL_R |= 0x100; //enables the timer after its settings have been configured
}

void ping_trigger (void){
    STATE = LOW;
    // Disable timer and disable timer interrupt
    TIMER3_CTL_R &= ~0x100;
    TIMER3_IMR_R & ~0x400;
    // Disable alternate function (disconnect timer from port pin)
    GPIO_PORTB_AFSEL_R &= 0xF7;
    GPIO_PORTB_DIR_R |= 0x8;
    // YOUR CODE HERE FOR PING TRIGGER/START PULSE
    GPIO_PORTB_DATA_R &= 0xF7;

    GPIO_PORTB_DATA_R |= 0x08;
    timer_waitMicros(5);
    GPIO_PORTB_DATA_R &= 0xF7;
    //GPIO_PORTB_DIR_R &= ~0x8;

    // Clear an interrupt that may have been erroneously triggered
    TIMER3_ICR_R |= 0x400; //Clears Timer B Interrupts

    // Re-enable alternate function, timer interrupt, and timer
    GPIO_PORTB_AFSEL_R |= 0x8;
    TIMER3_IMR_R |= 0x400;
    TIMER3_CTL_R |= 0x100;
} //TIMER3 may not be correct, if errors occur, double check these registers

void TIMER3B_Handler(void){

  // YOUR CODE HERE
  // As needed, go back to review your interrupt handler code for the UART lab.
  // What are the first lines of code in the ISR? Regardless of the device, interrupt handling
  // includes checking the source of the interrupt and clearing the interrupt status bit.
  // Checking the source: test the MIS bit in the MIS register (is the ISR executing
  // because the input capture event happened and interrupts were enabled for that event?
  // Clearing the interrupt: set the ICR bit (so that same event doesn't trigger another interrupt)
  // The rest of the code in the ISR depends on actions needed when the event happens.


    //if(TIMER3_MIS_R &= 0x400 == 1) {
        if (STATE == LOW) {
            START_TIME = TIMER3_TBR_R;
            STATE = HIGH;
        } else if (STATE == HIGH) {
            END_TIME = TIMER3_TBR_R;
            STATE = DONE;
        }
    //}
    TIMER3_ICR_R |= 0x400;
}

float ping_getDistance (void){

    // YOUR CODE HERE

    ping_trigger();

    float distance;
    uint8_t currentOverflow = 0;

    while (STATE != DONE) {}; //busy waits

    //currentOverflow = START_TIME < END_TIME;

    if (START_TIME < END_TIME) {
        TOTAL_TIME = START_TIME + (0xFFFFFF - END_TIME); //34300 cm / s - speed of sound
        //lcd_printf("overflow occurred");
        overflow_count++;
    } else {
        TOTAL_TIME = START_TIME - END_TIME;
    }

    distance = ((1.0 / 16000000) * TOTAL_TIME * 34300) / 2.0;





    return distance;
    // 1/ 16,000,000 * total clock cycles / 2

    //ping_trigger();
}

uint8_t get_totalOverflow(void) {
    return overflow_count;
}
