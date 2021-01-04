#include <display/DisplayBoundary_SSD1306.hpp>
#include <climits>


#define MY_OLED OLED_128x32
#define OLED_WIDTH 128
#define OLED_HEIGHT 32
DisplayBoundary_SSD1306::DisplayBoundary_SSD1306(SSD1306Configuration &config, PMSVSettings &settings)
        : settings{settings}, configuration{config}{
    pinMode(config.pin_vcc, OUTPUT);
    pinMode(config.pin_gnd, OUTPUT);
    digitalWrite(config.pin_gnd, LOW);
    digitalWrite(config.pin_vcc, LOW);
    delay(50);
    digitalWrite(config.pin_vcc, HIGH);
    delay(50);

    oled_address = obdI2CInit(&obd, MY_OLED, 0x3C, 0, 0, 0, config.pin_sda, config.pin_scl, -1, 800000L); // use standard I2C bus at 400Khz


    if (oled_address == OLED_NOT_FOUND)
    {
        Serial.println("Problem connecting to OLED");
    } else {
        obdFill(&obd, 0, 1);
        obdSetBackBuffer(&obd, ucBackBuffer);
    }
}

void DisplayBoundary_SSD1306::update() {

}

void DisplayBoundary_SSD1306::setCursor(uint8_t x, uint8_t y) {
    cursor_x = font_width * x;
    cursor_y = font_height * y;
}

void DisplayBoundary_SSD1306::write(char *str) {
    int size = strlen(str);
    obdWriteString(&obd, 0, cursor_x, cursor_y, str, font_size, 0, 1);
    cursor_x += size * font_width;
}

void DisplayBoundary_SSD1306::newline() {
    cursor_x = 0;
    cursor_y += font_height;
}

void DisplayBoundary_SSD1306::clear() {
    obdFill(&obd, 0, 1);
    resetCursor();
}
