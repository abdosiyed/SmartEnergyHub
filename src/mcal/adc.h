#ifndef MCAL_ADC_H
#define MCAL_ADC_H

#include <Arduino.h>

class MCAL_ADC {
public:
    // Initialize ADC on specified pin
    static void init(uint8_t pin);
    
    // Read raw ADC value from pin
    static uint16_t read(uint8_t pin);
    
    // Read and average multiple samples
    static uint16_t readAveraged(uint8_t pin, uint8_t samples = 10);
};

#endif // MCAL_ADC_H
