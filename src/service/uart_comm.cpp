#include "uart_comm.h"
#include "../utilities/json_builder.h"
#include "../utilities/json_parser.h"
#include "../include/config.h"

UART_Comm::UART_Comm(Monitor* monitorPtr) 
    : monitor(monitorPtr), rxIndex(0) {
}

void UART_Comm::init() {
    MCAL_UART::init(UART_BAUD);
}

void UART_Comm::sendStatusJSON() {
    // Build JSON with all room data
    char jsonBuffer[512];
    JSON_Builder::buildStatusJSON(jsonBuffer, sizeof(jsonBuffer), monitor);
    
    // Send via UART
    MCAL_UART::println(jsonBuffer);
}

void UART_Comm::processIncomingData() {
    while (MCAL_UART::available()) {
        uint8_t rxByte = MCAL_UART::read();
        
        // Look for newline as end of command
        if (rxByte == '\n' || rxByte == '\r') {
            if (rxIndex > 0) {
                rxBuffer[rxIndex] = '\0';
                
                // Parse and execute command
                JSON_Parser::parseAndExecuteCommand(rxBuffer, monitor);
                
                // Reset buffer
                rxIndex = 0;
            }
        } else if (rxIndex < sizeof(rxBuffer) - 1) {
            rxBuffer[rxIndex++] = rxByte;
        }
    }
}
