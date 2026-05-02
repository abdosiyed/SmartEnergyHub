#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// ==================== SYSTEM CONSTANTS ====================
#define NUM_ROOMS 4
#define MAX_POWER_DEFAULT 1000       // Default room max power (W)
#define HOME_POWER_DEFAULT 4000      // Default home budget (W)
#define MAX_POWER_SENSOR 2000        // Max power that potentiometer can represent (W)
#define ADC_MAX_VALUE 4095           // ESP32 ADC max value
#define UART_BAUD 115200
#define UART_TX_INTERVAL 2000        // Send data to Flask every 2 seconds (ms)

// ==================== MCAL PINS ====================
// ADC pins for power sensors (potentiometers)
#define ADC_PIN_R1 34                // Room 1 (Living Room)
#define ADC_PIN_R2 35                // Room 2 (Kitchen)
#define ADC_PIN_R3 32                // Room 3 (Bedroom 1)
#define ADC_PIN_R4 33                // Room 4 (Bedroom 2)

// GPIO pins for manual switches
#define SWITCH_PIN_R1 18             // Room 1 switch
#define SWITCH_PIN_R2 19             // Room 2 switch
#define SWITCH_PIN_R3 21             // Room 3 switch
#define SWITCH_PIN_R4 22             // Room 4 switch

// GPIO pins for LEDs
#define LED_PIN_R1 13                // Room 1 LED
#define LED_PIN_R2 12                // Room 2 LED
#define LED_PIN_R3 14                // Room 3 LED
#define LED_PIN_R4 27                // Room 4 LED

// I2C for LCD
#define LCD_I2C_ADDR 0x27
#define LCD_COLS 20
#define LCD_ROWS 4
#define LCD_SDA_PIN 21               // Note: ESP32 standard I2C SDA
#define LCD_SCL_PIN 22               // Note: ESP32 standard I2C SCL

// ==================== TIMING CONSTANTS ====================
#define SWITCH_DEBOUNCE_MS 50        // Debounce time for switches
#define LED_BLINK_INTERVAL_MS 300    // LED blink interval during overload
#define LCD_UPDATE_INTERVAL_MS 500   // LCD refresh interval

// ==================== ROOM DEFINITIONS ====================
#define ROOM_1_NAME "Living Room"
#define ROOM_2_NAME "Kitchen"
#define ROOM_3_NAME "Bedroom 1"
#define ROOM_4_NAME "Bedroom 2"

#define ROOM_1_ID "R1"
#define ROOM_2_ID "R2"
#define ROOM_3_ID "R3"
#define ROOM_4_ID "R4"

#endif // CONFIG_H
