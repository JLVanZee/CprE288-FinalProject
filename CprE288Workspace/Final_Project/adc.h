/*
 * adc.h
 *
 *  Created on: Apr 29, 2023
 *
 *  PING))) Sensor
 */

#ifndef ADC_H_
#define ADC_H_


#include "Timer.h"
#include "lcd.h"
#include <stdbool.h>
#include "open_interface.h"

void adc_init(void);

/**
 * Call Function multiple times and average the value for a better reading
 */
uint32_t adc_read(void);


#endif /* ADC_H_ */
