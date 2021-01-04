#pragma once
#include <cstdint>
struct SSD1306Configuration {
    uint8_t width;
    uint8_t height;
    uint8_t pin_scl;
    uint8_t pin_sda;
    uint8_t pin_gnd;
    uint8_t pin_vcc;
    int address;

};