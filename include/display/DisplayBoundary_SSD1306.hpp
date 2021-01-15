/*
 * Copyright (c) 2021. Niels Post. AI Lab Vrije Universiteit Brussel.
 *
 * This file is part of MP-Firm.
 *
 * MP-Firm is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * MP-Firm is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with MP-Firm.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once
#include <core/util/ArduinoSafe.hpp>

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

