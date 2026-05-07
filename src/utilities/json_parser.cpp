#include "json_parser.h"
#include <string.h>
#include <stdlib.h>

// Helper function to extract string value from JSON
static bool extractString(const char* json, const char* key, char* out, size_t outSize) {
    const char* keyStart = strstr(json, key);
    if (!keyStart) return false;
    
    const char* colonPos = strchr(keyStart, ':');
    if (!colonPos) return false;
    
    const char* quoteStart = strchr(colonPos, '"');
    if (!quoteStart) return false;
    quoteStart++;  // Move past opening quote
    
    const char* quoteEnd = strchr(quoteStart, '"');
    if (!quoteEnd) return false;
    
    size_t len = quoteEnd - quoteStart;
    if (len >= outSize) len = outSize - 1;
    
    strncpy(out, quoteStart, len);
    out[len] = '\0';
    
    return true;
}

// Helper function to extract integer value from JSON
static bool extractInt(const char* json, const char* key, int* out) {
    const char* keyStart = strstr(json, key);
    if (!keyStart) return false;
    
    const char* colonPos = strchr(keyStart, ':');
    if (!colonPos) return false;
    
    const char* numStart = colonPos + 1;
    while (*numStart == ' ' || *numStart == ':') numStart++;
    
    *out = atoi(numStart);
    return true;
}

void JSON_Parser::parseAndExecuteCommand(const char* jsonStr, Monitor* monitor) {
    if (!jsonStr || strlen(jsonStr) == 0) return;
    
    char cmd[32] = {0};
    char room[8] = {0};
    int value = 0;
    
    // Extract command
    if (!extractString(jsonStr, "\"cmd\"", cmd, sizeof(cmd))) {
        return;
    }
    
    // Handle TOGGLE command
    if (strcmp(cmd, "TOGGLE") == 0) {
        if (extractString(jsonStr, "\"room\"", room, sizeof(room))) {
            // Find room index
            for (uint8_t i = 0; i < NUM_ROOMS; i++) {
                if (strcmp(monitor->getRoom(i)->getId(), room) == 0) {
                    monitor->toggleRoom(i);
                    break;
                }
            }
        }
    }
    // Handle SET_MP (Set Max Power for room)
    else if (strcmp(cmd, "SET_MP") == 0) {
        if (extractString(jsonStr, "\"room\"", room, sizeof(room)) &&
            extractInt(jsonStr, "\"value\"", &value)) {
            // Find room index
            for (uint8_t i = 0; i < NUM_ROOMS; i++) {
                if (strcmp(monitor->getRoom(i)->getId(), room) == 0) {
                    monitor->setRoomMaxPower(i, (uint16_t)value);
                    break;
                }
            }
        }
    }
    // Handle SET_HP (Set Home Power budget)
    else if (strcmp(cmd, "SET_HP") == 0) {
        if (extractInt(jsonStr, "\"value\"", &value)) {
            monitor->setHomePowerBudget((uint16_t)value);
        }
    }
}
