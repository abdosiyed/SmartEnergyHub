#ifndef HAL_LED_H
#define HAL_LED_H

#include "../mcal/gpio.h"
#include "../mcal/timer.h"

class HAL_LED {
public:
    // Initialize LED on specified pin
    static void init(uint8_t pin);
    
    // Turn LED on
    static void on(uint8_t pin);
    
    // Turn LED off
    static void off(uint8_t pin);
    
    // Toggle LED
    static void toggle(uint8_t pin);
    
    // Blink LED with given interval (returns true if currently ON during blink cycle)
    static bool blink(uint8_t pin, unsigned long interval);
};

#endif // HAL_LED_H
