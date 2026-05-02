#ifndef MCAL_GPIO_H
#define MCAL_GPIO_H

#include <Arduino.h>

class MCAL_GPIO {
public:
    // Configure GPIO as output
    static void initOutput(uint8_t pin);
    
    // Configure GPIO as input with pull-up
    static void initInputPullup(uint8_t pin);
    
    // Write digital value to pin
    static void write(uint8_t pin, uint8_t level);
    
    // Read digital value from pin
    static uint8_t read(uint8_t pin);
};

#endif // MCAL_GPIO_H
