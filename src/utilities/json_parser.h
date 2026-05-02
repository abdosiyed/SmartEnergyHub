#ifndef UTILITIES_JSON_PARSER_H
#define UTILITIES_JSON_PARSER_H

#include "../service/monitor.h"

class JSON_Parser {
public:
    // Parse incoming JSON command and execute on monitor
    // Supported commands:
    // {"cmd":"TOGGLE","room":"R1"}
    // {"cmd":"SET_MP","room":"R1","value":1500}
    // {"cmd":"SET_HP","value":5000}
    static void parseAndExecuteCommand(const char* jsonStr, Monitor* monitor);
};

#endif // UTILITIES_JSON_PARSER_H
