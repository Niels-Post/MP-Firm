#pragma once

#include <core/PMSVSettings.hpp>
#include "BaseDisplayBoundary.hpp"

class DisplayController {
    BaseDisplayBoundary &displayBoundary;
    PMSVSettings &pmsvSettings;


    uint8_t last_robot_id = 255;

public:
    DisplayController(BaseDisplayBoundary &displayBoundary, PMSVSettings &pmsvSettings);

    void update();

    void display();
};