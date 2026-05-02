#ifndef SERVICE_ROOM_H
#define SERVICE_ROOM_H

#include <Arduino.h>

class Room {
private:
    const char* id;
    const char* name;
    uint16_t currentPower;
    uint8_t state;  // 1 = ON, 0 = OFF
    uint16_t maxPowerLimit;
    
public:
    Room(const char* roomId, const char* roomName);
    
    // Getters
    const char* getId() const;
    const char* getName() const;
    uint16_t getPower() const;
    uint8_t getState() const;
    uint16_t getMaxPowerLimit() const;
    
    // Setters
    void setPower(uint16_t power);
    void setState(uint8_t newState);
    void setMaxPowerLimit(uint16_t limit);
    
    // Utilities
    bool isOverloaded() const;
};

#endif // SERVICE_ROOM_H
