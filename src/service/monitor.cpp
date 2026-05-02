#include "monitor.h"
#include "config.h"

Monitor::Monitor() : homePowerBudget(HOME_POWER_DEFAULT), currentState(MONITORING), overloadedRoomIndex(255) {
    // Create rooms
    rooms[0] = new Room(ROOM_1_ID, ROOM_1_NAME);
    rooms[1] = new Room(ROOM_2_ID, ROOM_2_NAME);
    rooms[2] = new Room(ROOM_3_ID, ROOM_3_NAME);
    rooms[3] = new Room(ROOM_4_ID, ROOM_4_NAME);
}

void Monitor::init() {
    // Initialize each room with default max power
    for (uint8_t i = 0; i < NUM_ROOMS; i++) {
        rooms[i]->setMaxPowerLimit(MAX_POWER_DEFAULT);
    }
}

Room* Monitor::getRoom(uint8_t index) {
    if (index < NUM_ROOMS) {
        return rooms[index];
    }
    return nullptr;
}

void Monitor::updateState() {
    // Check for room overload first
    for (uint8_t i = 0; i < NUM_ROOMS; i++) {
        if (rooms[i]->isOverloaded()) {
            currentState = ROOM_OVERLOAD_ALERT;
            overloadedRoomIndex = i;
            return;
        }
    }
    
    // Check for home overload
    if (getTotalPower() > homePowerBudget) {
        currentState = HOME_OVERLOAD_ALERT;
        overloadedRoomIndex = 255;
        return;
    }
    
    // Normal monitoring
    currentState = MONITORING;
    overloadedRoomIndex = 255;
}

uint16_t Monitor::getTotalPower() const {
    uint16_t total = 0;
    for (uint8_t i = 0; i < NUM_ROOMS; i++) {
        // Only count power if room is ON
        if (rooms[i]->getState() == 1) {
            total += rooms[i]->getPower();
        }
    }
    return total;
}

SystemState Monitor::getState() const {
    return currentState;
}

uint8_t Monitor::getOverloadedRoomIndex() const {
    return overloadedRoomIndex;
}

void Monitor::setHomePowerBudget(uint16_t budget) {
    homePowerBudget = budget;
}

uint16_t Monitor::getHomePowerBudget() const {
    return homePowerBudget;
}

void Monitor::toggleRoom(uint8_t roomIndex) {
    if (roomIndex < NUM_ROOMS) {
        uint8_t currentState = rooms[roomIndex]->getState();
        rooms[roomIndex]->setState(currentState == 1 ? 0 : 1);
    }
}

void Monitor::setRoomMaxPower(uint8_t roomIndex, uint16_t limit) {
    if (roomIndex < NUM_ROOMS) {
        rooms[roomIndex]->setMaxPowerLimit(limit);
    }
}
