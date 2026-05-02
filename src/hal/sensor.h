#ifndef HAL_SENSOR_H
#define HAL_SENSOR_H

#include "../mcal/adc.h"

class HAL_Sensor {
public:
    // Initialize power sensor on ADC pin
    static void init(uint8_t adcPin);
    
    // Read power value in Watts (0-2000W) from ADC pin
    // Maps ADC value (0-4095) to power range (0-2000W)
    static uint16_t readPowerWatts(uint8_t adcPin);
};

#endif // HAL_SENSOR_H
