#ifndef SERVICE_MONITOR_H
#define SERVICE_MONITOR_H

#include "room.h"
#include "../include/config.h"

// System states
enum SystemState {
    MONITORING = 0,
    ROOM_OVERLOAD_ALERT = 1,
    HOME_OVERLOAD_ALERT = 2
};

class Monitor {
private:
    Room* rooms[NUM_ROOMS];
    uint16_t homePowerBudget;
    SystemState currentState;
    uint8_t overloadedRoomIndex;  // Index of overloaded room (-1 if none)
    
public:
    Monitor();
    
    // Initialize monitor with room array
    void init();
    
    // Get room by index
    Room* getRoom(uint8_t index);
    
    // Update system state based on current power readings
    void updateState();
    
    // Get total power consumption across all rooms
    uint16_t getTotalPower() const;
    
    // Get current system state
    SystemState getState() const;
    
    // Get index of overloaded room (255 if no overload)
    uint8_t getOverloadedRoomIndex() const;
    
    // Set home power budget
    void setHomePowerBudget(uint16_t budget);
    
    // Get home power budget
    uint16_t getHomePowerBudget() const;
    
    // Toggle room state
    void toggleRoom(uint8_t roomIndex);
    
    // Set room max power limit
    void setRoomMaxPower(uint8_t roomIndex, uint16_t limit);
};

#endif // SERVICE_MONITOR_H
