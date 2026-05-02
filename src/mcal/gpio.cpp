#include "gpio.h"

void MCAL_GPIO::initOutput(uint8_t pin) {
    pinMode(pin, OUTPUT);
}

void MCAL_GPIO::initInputPullup(uint8_t pin) {
    pinMode(pin, INPUT_PULLUP);
}

void MCAL_GPIO::write(uint8_t pin, uint8_t level) {
    digitalWrite(pin, level);
}

uint8_t MCAL_GPIO::read(uint8_t pin) {
    return digitalRead(pin);
}
