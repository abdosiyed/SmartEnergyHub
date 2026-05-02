#include "timer.h"

unsigned long MCAL_Timer::millis() {
    return ::millis();
}

unsigned long MCAL_Timer::micros() {
    return ::micros();
}

bool MCAL_Timer::hasTimedOut(unsigned long startTime, unsigned long interval) {
    return (::millis() - startTime) >= interval;
}
