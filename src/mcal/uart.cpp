#include "uart.h"

void MCAL_UART::init(uint32_t baudRate) {
    Serial.begin(baudRate);
}

bool MCAL_UART::available() {
    return Serial.available();
}

uint8_t MCAL_UART::read() {
    return Serial.read();
}

void MCAL_UART::write(uint8_t data) {
    Serial.write(data);
}

void MCAL_UART::print(const char* str) {
    Serial.print(str);
}

void MCAL_UART::println(const char* str) {
    Serial.println(str);
}
