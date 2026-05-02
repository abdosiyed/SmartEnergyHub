#include "led.h"

void HAL_LED::init(uint8_t pin) {
    MCAL_GPIO::initOutput(pin);
    MCAL_GPIO::write(pin, LOW);
}

void HAL_LED::on(uint8_t pin) {
    MCAL_GPIO::write(pin, HIGH);
}

void HAL_LED::off(uint8_t pin) {
    MCAL_GPIO::write(pin, LOW);
}

void HAL_LED::toggle(uint8_t pin) {
    uint8_t current = MCAL_GPIO::read(pin);
    MCAL_GPIO::write(pin, !current);
}

bool HAL_LED::blink(uint8_t pin, unsigned long interval) {
    static unsigned long blinkStartTime = 0;
    static bool isBlinkOn = false;
    
    unsigned long currentTime = MCAL_Timer::millis();
    unsigned long halfInterval = interval / 2;
    
    if (currentTime - blinkStartTime >= interval) {
        blinkStartTime = currentTime;
        isBlinkOn = !isBlinkOn;
    }
    
    if (isBlinkOn) {
        MCAL_GPIO::write(pin, HIGH);
        return true;
    } else {
        MCAL_GPIO::write(pin, LOW);
        return false;
    }
}
