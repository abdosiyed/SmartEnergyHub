#ifndef HAL_LCD_H
#define HAL_LCD_H

#include "../mcal/gpio.h"
#include "../mcal/timer.h"
#include <LiquidCrystal_I2C.h>

class HAL_LCD {
private:
    static LiquidCrystal_I2C lcd;
    
public:
    // Initialize LCD
    static void init();
    
    // Clear display
    static void clear();
    
    // Set cursor position (row, col)
    static void setCursor(uint8_t row, uint8_t col);
    
    // Print string at current cursor position
    static void print(const char* str);
    
    // Print at specified position
    static void printAt(uint8_t row, uint8_t col, const char* str);
    
    // Turn on backlight
    static void backlightOn();
    
    // Turn off backlight
    static void backlightOff();
};

#endif // HAL_LCD_H
