#include "adc.h"

void MCAL_ADC::init(uint8_t pin) {
    pinMode(pin, INPUT);
    // ADC is configured by Arduino framework automatically for ESP32
}

uint16_t MCAL_ADC::read(uint8_t pin) {
    return analogRead(pin);
}

uint16_t MCAL_ADC::readAveraged(uint8_t pin, uint8_t samples) {
    uint32_t sum = 0;
    for (uint8_t i = 0; i < samples; i++) {
        sum += analogRead(pin);
        delayMicroseconds(100);  // Small delay between reads
    }
    return sum / samples;
}
