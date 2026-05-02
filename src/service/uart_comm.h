#ifndef SERVICE_UART_COMM_H
#define SERVICE_UART_COMM_H

#include "../mcal/uart.h"
#include "monitor.h"
#include "config.h"

class UART_Comm {
private:
    Monitor* monitor;
    char rxBuffer[512];
    uint16_t rxIndex;
    
public:
    UART_Comm(Monitor* monitorPtr);
    
    // Initialize UART communication
    void init();
    
    // Send JSON data to Flask (room states and total power)
    void sendStatusJSON();
    
    // Process incoming commands from UART
    void processIncomingData();
};

#endif // SERVICE_UART_COMM_H
