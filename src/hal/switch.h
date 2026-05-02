#ifndef HAL_SWITCH_H
#define HAL_SWITCH_H

#include "../mcal/gpio.h"
#include "../mcal/timer.h"

class HAL_Switch {
private:
    uint8_t pin;
    unsigned long lastChangeTime;
    uint8_t lastState;
    
public:
    HAL_Switch(uint8_t switchPin);
    
    // Initialize switch on specified pin
    void init();
    
    // Read switch state with debouncing (returns 1 if pressed, 0 if not)
    uint8_t readDebounced(unsigned long debounceMs);
    
    // Get last debounced state
    uint8_t getState();
};

#endif // HAL_SWITCH_H
