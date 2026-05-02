#ifndef UTILITIES_JSON_BUILDER_H
#define UTILITIES_JSON_BUILDER_H

#include "../service/monitor.h"

class JSON_Builder {
public:
    // Build JSON status string with all room data
    // Format: {"R1":{"name":"...", "power":..., "state":"ON/OFF"}, ...}
    static void buildStatusJSON(char* buffer, size_t bufferSize, Monitor* monitor);
};

#endif // UTILITIES_JSON_BUILDER_H
