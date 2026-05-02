#include "lcd.h"
#include "config.h"

// Static member initialization
LiquidCrystal_I2C HAL_LCD::lcd(LCD_I2C_ADDR, LCD_COLS, LCD_ROWS);

void HAL_LCD::init() {
    lcd.init();
    lcd.backlight();
    lcd.clear();
}

void HAL_LCD::clear() {
    lcd.clear();
}

void HAL_LCD::setCursor(uint8_t row, uint8_t col) {
    lcd.setCursor(col, row);
}

void HAL_LCD::print(const char* str) {
    lcd.print(str);
}

void HAL_LCD::printAt(uint8_t row, uint8_t col, const char* str) {
    lcd.setCursor(col, row);
    lcd.print(str);
}

void HAL_LCD::backlightOn() {
    lcd.backlight();
}

void HAL_LCD::backlightOff() {
    lcd.noBacklight();
}
