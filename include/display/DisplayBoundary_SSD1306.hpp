#pragma once
#include <Arduino.h>


#include <OneBitDisplay.h>
#include <core/PMSVSettings.hpp>
#include <core/display/BaseDisplayBoundary.hpp>
#include "SSD1306Configuration.hpp"


class DisplayBoundary_SSD1306: public BaseDisplayBoundary {
    PMSVSettings &settings;
    OBDISP obd;
    uint8_t ucBackBuffer[512];
    int oled_address;
    SSD1306Configuration &configuration;
    int font_size = FONT_6x8;
    int font_width = 6;
    int font_height = 8;

    int cursor_x = 0;
    int cursor_y = 0;


public:
    DisplayBoundary_SSD1306(SSD1306Configuration &config, PMSVSettings &settings);

    void update();

    void clear() override;

    void setCursor(uint8_t x, uint8_t y) override;

    void write(char *str) override;

    void newline() override;
};

