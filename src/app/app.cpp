#include "app/app.h"
#include "mcal/timer.h"
#include "config.h"

App::App() : lastUARTSendTime(0) {
    // Initialize service layer
    monitor = new Monitor();
    uartComm = new UART_Comm(monitor);
    display = new Display(monitor);
    
    // Initialize hardware switches
    switches[0] = new HAL_Switch(SWITCH_PIN_R1);
    switches[1] = new HAL_Switch(SWITCH_PIN_R2);
    switches[2] = new HAL_Switch(SWITCH_PIN_R3);
    switches[3] = new HAL_Switch(SWITCH_PIN_R4);
}

void App::init() {
    // Initialize UART communication
    uartComm->init();
    
    // Initialize monitor
    monitor->init();
    
    // Initialize display
    display->init();
    
    // Initialize all hardware interfaces
    for (uint8_t i = 0; i < NUM_ROOMS; i++) {
        // Initialize power sensors
        HAL_Sensor::init(i == 0 ? ADC_PIN_R1 : 
                        i == 1 ? ADC_PIN_R2 : 
                        i == 2 ? ADC_PIN_R3 : ADC_PIN_R4);
        
        // Initialize LEDs
        uint8_t ledPin = i == 0 ? LED_PIN_R1 :
                         i == 1 ? LED_PIN_R2 :
                         i == 2 ? LED_PIN_R3 : LED_PIN_R4;
        HAL_LED::init(ledPin);
        
        // Initialize switches
        switches[i]->init();
    }
}

void App::run() {
    // Process switch inputs
    processSwitchInputs();
    
    // Update power readings from sensors
    updatePowerReadings();
    
    // Update system state based on power readings
    monitor->updateState();
    
    // Update LED indicators
    updateLEDs();
    
    // Update display
    display->update();
    
    // Process incoming UART commands
    uartComm->processIncomingData();
    
    // Send status via UART at specified interval
    sendUARTStatus();
}

void App::processSwitchInputs() {
    for (uint8_t i = 0; i < NUM_ROOMS; i++) {
        uint8_t switchPressed = switches[i]->readDebounced(SWITCH_DEBOUNCE_MS);
        
        if (switchPressed) {
            // Toggle room state on switch press
            monitor->toggleRoom(i);
        }
    }
}

void App::updatePowerReadings() {
    uint8_t adcPins[NUM_ROOMS] = {ADC_PIN_R1, ADC_PIN_R2, ADC_PIN_R3, ADC_PIN_R4};
    
    for (uint8_t i = 0; i < NUM_ROOMS; i++) {
        uint16_t power = HAL_Sensor::readPowerWatts(adcPins[i]);
        monitor->getRoom(i)->setPower(power);
    }
}

void App::updateLEDs() {
    uint8_t ledPins[NUM_ROOMS] = {LED_PIN_R1, LED_PIN_R2, LED_PIN_R3, LED_PIN_R4};
    
    SystemState state = monitor->getState();
    
    if (state == MONITORING) {
        // Normal mode: LED ON/OFF based on room state
        for (uint8_t i = 0; i < NUM_ROOMS; i++) {
            if (monitor->getRoom(i)->getState() == 1) {
                HAL_LED::on(ledPins[i]);
            } else {
                HAL_LED::off(ledPins[i]);
            }
        }
    } 
    else if (state == ROOM_OVERLOAD_ALERT) {
        // Room overload: blink overloaded room LED
        uint8_t overloadIdx = monitor->getOverloadedRoomIndex();
        
        for (uint8_t i = 0; i < NUM_ROOMS; i++) {
            if (i == overloadIdx) {
                // Blink the overloaded room's LED
                HAL_LED::blink(ledPins[i], LED_BLINK_INTERVAL_MS);
            } else {
                // Keep other LEDs on/off based on state
                if (monitor->getRoom(i)->getState() == 1) {
                    HAL_LED::on(ledPins[i]);
                } else {
                    HAL_LED::off(ledPins[i]);
                }
            }
        }
    }
    else if (state == HOME_OVERLOAD_ALERT) {
        // Home overload: blink all LEDs together
        for (uint8_t i = 0; i < NUM_ROOMS; i++) {
            HAL_LED::blink(ledPins[i], LED_BLINK_INTERVAL_MS);
        }
    }
}

void App::sendUARTStatus() {
    unsigned long currentTime = MCAL_Timer::millis();
    
    if (currentTime - lastUARTSendTime >= UART_TX_INTERVAL) {
        lastUARTSendTime = currentTime;
        uartComm->sendStatusJSON();
    }
}
