#ifndef APP_H
#define APP_H

#include "service/monitor.h"
#include "service/uart_comm.h"
#include "service/display.h"
#include "hal/led.h"
#include "hal/switch.h"
#include "hal/sensor.h"
#include "config.h"

class App {
private:
    Monitor* monitor;
    UART_Comm* uartComm;
    Display* display;
    
    // Hardware abstraction layers
    HAL_Switch* switches[NUM_ROOMS];
    
    // Timing control
    unsigned long lastUARTSendTime;
    
public:
    App();
    
    // Initialize application and all hardware
    void init();
    
    // Main application loop
    void run();
    
private:
    // Handle switch inputs from hardware
    void processSwitchInputs();
    
    // Read power sensors and update room states
    void updatePowerReadings();
    
    // Handle LED control based on system state
    void updateLEDs();
    
    // Send status via UART at specified interval
    void sendUARTStatus();
};

#endif // APP_H
