#ifndef MCAL_UART_H
#define MCAL_UART_H

#include <Arduino.h>

class MCAL_UART {
public:
    // Initialize UART with specified baud rate
    static void init(uint32_t baudRate);
    
    // Check if data is available in serial buffer
    static bool available();
    
    // Read a single byte from serial buffer
    static uint8_t read();
    
    // Write a single byte to serial port
    static void write(uint8_t data);
    
    // Write a string to serial port
    static void print(const char* str);
    
    // Write a string with newline
    static void println(const char* str);
};

#endif // MCAL_UART_H
