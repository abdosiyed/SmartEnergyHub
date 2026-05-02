#include "room.h"

Room::Room(const char* roomId, const char* roomName)
    : id(roomId), name(roomName), currentPower(0), state(0), maxPowerLimit(1000) {
}

const char* Room::getId() const {
    return id;
}

const char* Room::getName() const {
    return name;
}

uint16_t Room::getPower() const {
    return currentPower;
}

uint8_t Room::getState() const {
    return state;
}

uint16_t Room::getMaxPowerLimit() const {
    return maxPowerLimit;
}

void Room::setPower(uint16_t power) {
    currentPower = power;
}

void Room::setState(uint8_t newState) {
    state = newState;
}

void Room::setMaxPowerLimit(uint16_t limit) {
    maxPowerLimit = limit;
}

bool Room::isOverloaded() const {
    // Overloaded if ON and power exceeds limit
    return (state == 1) && (currentPower > maxPowerLimit);
}
