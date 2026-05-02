#ifndef MCAL_TIMER_H
#define MCAL_TIMER_H

#include <Arduino.h>

class MCAL_Timer {
public:
    // Get current system time in milliseconds
    static unsigned long millis();
    
    // Get current system time in microseconds
    static unsigned long micros();
    
    // Check if timeout has elapsed
    static bool hasTimedOut(unsigned long startTime, unsigned long interval);
};

#endif // MCAL_TIMER_H
