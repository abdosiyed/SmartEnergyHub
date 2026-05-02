#include "switch.h"

HAL_Switch::HAL_Switch(uint8_t switchPin) 
    : pin(switchPin), lastChangeTime(0), lastState(HIGH) {
}

void HAL_Switch::init() {
    MCAL_GPIO::initInputPullup(pin);
    lastState = MCAL_GPIO::read(pin);
    lastChangeTime = MCAL_Timer::millis();
}

uint8_t HAL_Switch::readDebounced(unsigned long debounceMs) {
    uint8_t currentReading = MCAL_GPIO::read(pin);
    unsigned long currentTime = MCAL_Timer::millis();
    
    // If reading changed
    if (currentReading != lastState) {
        // Reset timer
        lastChangeTime = currentTime;
        lastState = currentReading;
    }
    
    // If stable for debounce period and switch is pressed (LOW), return 1
    if ((currentTime - lastChangeTime) >= debounceMs) {
        if (currentReading == LOW) {
            return 1;  // Switch pressed
        }
    }
    
    return 0;  // Switch not pressed or bouncing
}

uint8_t HAL_Switch::getState() {
    return lastState;
}
