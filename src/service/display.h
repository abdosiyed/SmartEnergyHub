#ifndef SERVICE_DISPLAY_H
#define SERVICE_DISPLAY_H

#include "../hal/lcd.h"
#include "monitor.h"
#include "../mcal/timer.h"

class Display {
private:
    Monitor* monitor;
    unsigned long lastUpdateTime;
    
public:
    Display(Monitor* monitorPtr);
    
    // Initialize display
    void init();
    
    // Update LCD based on system state
    void update();
    
private:
    // Display monitoring state
    void displayMonitoring();
    
    // Display room overload state
    void displayRoomOverload();
    
    // Display home overload state
    void displayHomeOverload();
    
    // Utility to format power with padding
    void formatPower(char* buffer, uint16_t power);
};

#endif // SERVICE_DISPLAY_H
