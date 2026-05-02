#include "display.h"
#include <cstdio>
#include <cstring>

Display::Display(Monitor* monitorPtr)
    : monitor(monitorPtr), lastUpdateTime(0) {
}

void Display::init() {
    HAL_LCD::init();
}

void Display::update() {
    unsigned long currentTime = MCAL_Timer::millis();
    
    // Update LCD at specified interval
    if (currentTime - lastUpdateTime < LCD_UPDATE_INTERVAL_MS) {
        return;
    }
    lastUpdateTime = currentTime;
    
    HAL_LCD::clear();
    
    switch (monitor->getState()) {
        case MONITORING:
            displayMonitoring();
            break;
        case ROOM_OVERLOAD_ALERT:
            displayRoomOverload();
            break;
        case HOME_OVERLOAD_ALERT:
            displayHomeOverload();
            break;
    }
}

void Display::displayMonitoring() {
    char line[21] = {0};
    
    // Row 0: R1 and R2 power
    snprintf(line, sizeof(line), "LR:%4uW   KT:%4uW", 
             monitor->getRoom(0)->getPower(),
             monitor->getRoom(1)->getPower());
    HAL_LCD::printAt(0, 0, line);
    
    // Row 1: R3 and R4 power
    snprintf(line, sizeof(line), "B1:%4uW   B2:%4uW",
             monitor->getRoom(2)->getPower(),
             monitor->getRoom(3)->getPower());
    HAL_LCD::printAt(1, 0, line);
    
    // Row 2: Total power
    snprintf(line, sizeof(line), "Total: %5uW", monitor->getTotalPower());
    HAL_LCD::printAt(2, 0, line);
    
    // Row 3: Status
    HAL_LCD::printAt(3, 0, "Status: NORMAL     ");
}

void Display::displayRoomOverload() {
    char line[21] = {0};
    uint8_t roomIdx = monitor->getOverloadedRoomIndex();
    Room* room = monitor->getRoom(roomIdx);
    
    // Row 0
    HAL_LCD::printAt(0, 0, "!! ROOM OVERLOAD !!");
    
    // Row 1: Room name and current power
    snprintf(line, sizeof(line), "%-15s%4uW", room->getName(), room->getPower());
    HAL_LCD::printAt(1, 0, line);
    
    // Row 2: Limit
    snprintf(line, sizeof(line), "Limit: %11uW", room->getMaxPowerLimit());
    HAL_LCD::printAt(2, 0, line);
    
    // Row 3
    HAL_LCD::printAt(3, 0, "Turn OFF or Check ");
}

void Display::displayHomeOverload() {
    char line[21] = {0};
    
    // Row 0
    HAL_LCD::printAt(0, 0, "!! HOME OVERLOAD !!");
    
    // Row 1
    HAL_LCD::printAt(1, 0, "               ");
    
    // Row 2: Total and budget
    snprintf(line, sizeof(line), "T:%5uW  B:%5uW", 
             monitor->getTotalPower(),
             monitor->getHomePowerBudget());
    HAL_LCD::printAt(2, 0, line);
    
    // Row 3
    HAL_LCD::printAt(3, 0, "Reduce Usage!      ");
}

void Display::formatPower(char* buffer, uint16_t power) {
    snprintf(buffer, 6, "%5u", power);
}
