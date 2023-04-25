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
#include "cyBot_Scan.h"  // For scan sensors
#include <stdbool.h>
#include "open_interface.h"

//#include <unistd.h>

/*
 *  DATA FOR IR SENSOR DATA
 * Column1  Column2
    9 cm    3146
    15 cm   2152
    20 cm   1681
    25 cm   1488
    30 cm   1328
    35 cm   1090
    40 cm   910
    45 cm   739
    50 cm   594
 *
 */


int main(void) { //y = 6E+06x^-1.662

    timer_init(); // Must be called before lcd_init(), which uses timer functions
    lcd_init();
    cyBOT_init_Scan(0b0111);
    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);
    uart_init();
    cyBOT_init_Scan(0b0111);
    cyBOT_Scan_t scanner;

    right_calibration_value = 285250; //CyBot 12 calibration
    left_calibration_value = 1256500;
    adc_init();
    uint32_t num = 0;
    int i, j;
    char buffer;

    double calculatedDistance;

    cyBOT_Scan(90, &scanner);

    for (i = 0; i < 20; ++i) {
        buffer = uart_receive(); //Waits for a random input, then will take 16 samples and averages them, using the average in the equation

        for (j = 0; j < 16; ++j) {
             num += adc_read();
        }

        num /= 16;

        //calculatedDistance = (-2 * pow(10, -12) * pow(num, 4)) + (pow(10, -8) * pow(num, 3)) - (3 * pow(10, -5) * pow(num, 2)) - (0.0103 * num) + 62.411;
        //calculatedDistance = -2E-12*pow(num, 4) + 1E-08*pow(num, 3) - 3E-05*pow(num, 2) - 0.0103*num + 62.411;
        //calculatedDistance = 7E-06*pow(num, 2) - 0.0421*num + 72.53;
        calculatedDistance = 6E+06 * pow(num, -1.662);
        lcd_printf("Avg Quantized Value: %d\nCalculated Distance: %.2lf", num, calculatedDistance);
    }

    // y = 6E+06x^-1.662
    // y = -2E-12x4 + 1E-08x3 - 3E-05x2 - 0.0103x + 62.4111 IDEAL EQUATION FOR CM CONVERSION

    return 0;
}

uint32_t adc_read(void){

  uint32_t result;

  ADC0_PSSI_R = 0x0008;            // 1) initiate SS3

  while((ADC0_RIS_R&0x08)==0){};   // 2) wait for conversion done

  result = ADC0_SSFIFO3_R&0xFFF;   // 3) read result

  ADC0_ISC_R = 0x0008;             // 4) acknowledge completion

  return result;

}

void adc_init(void) {




    SYSCTL_RCGCADC_R |= 0x0001;
    SYSCTL_RCGCGPIO_R |= 0x1;
    while((SYSCTL_PRGPIO_R&0x10) != 0x10){};
    GPIO_PORTB_DIR_R &= 0x10;
    GPIO_PORTB_AFSEL_R |= 0x10;
    GPIO_PORTB_DEN_R &= ~0x10;
    GPIO_PORTB_AMSEL_R |= 0x10;
    // while((SYSCTL_PRADC_R&0x0001) != 0x0001){};
    ADC0_PC_R &= ~0xF;
    ADC0_ACTSS_R &= ~0x0008;
    ADC0_EMUX_R &= ~0xF000;
    ADC0_SSMUX3_R &= ~0x000F;
    ADC0_SSMUX3_R += 10;
    ADC0_SSCTL3_R = 0x0006;
    ADC0_IM_R &= ~0x0008;
    ADC0_ACTSS_R |= 0x0008;



} // y = -2E-12x^4 + 1E-8x^3 - 3E-5x^20.0103x + 62.411 IDEAL EQUATION FOR CM CONVERSION
