#include "json_builder.h"
#include "config.h"
#include <stdio.h>
#include <string.h>

void JSON_Builder::buildStatusJSON(char* buffer, size_t bufferSize, Monitor* monitor) {
    // Build JSON manually to avoid ArduinoJson serialization overhead
    // Format: {"R1":{"name":"Living Room","power":850,"state":"ON"},...,"total":2950}
    
    char* pos = buffer;
    int remaining = bufferSize;
    
    pos += snprintf(pos, remaining, "{");
    remaining = bufferSize - (pos - buffer);
    
    for (uint8_t i = 0; i < NUM_ROOMS; i++) {
        Room* room = monitor->getRoom(i);
        const char* stateStr = (room->getState() == 1) ? "ON" : "OFF";
        
        pos += snprintf(pos, remaining, "\"%s\":{\"name\":\"%s\",\"power\":%u,\"state\":\"%s\"}",
                       room->getId(),
                       room->getName(),
                       room->getPower(),
                       stateStr);
        remaining = bufferSize - (pos - buffer);
        
        if (i < NUM_ROOMS - 1) {
            pos += snprintf(pos, remaining, ",");
            remaining = bufferSize - (pos - buffer);
        }
    }
    
    pos += snprintf(pos, remaining, ",\"total\":%u}", monitor->getTotalPower());
}
