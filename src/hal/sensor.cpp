#include "sensor.h"
#include "config.h"

void HAL_Sensor::init(uint8_t adcPin) {
    MCAL_ADC::init(adcPin);
}

uint16_t HAL_Sensor::readPowerWatts(uint8_t adcPin) {
    uint16_t adcValue = MCAL_ADC::readAveraged(adcPin, 10);
    // Linear mapping: ADC 0-4095 -> Power 0-2000W
    uint16_t powerWatts = (adcValue * MAX_POWER_SENSOR) / ADC_MAX_VALUE;
    return powerWatts;
}
