#pragma once

#include <core/PMSVSettings.hpp>
#include "BaseDisplayBoundary.hpp"

/**
 * Controller class to manage a text display and output (currently) the robot id to it
 */
class DisplayController {
    /// DisplayBoundary to output to
    BaseDisplayBoundary &displayBoundary;
    /// Settings object to get displayed parameters from
    PMSVSettings &pmsvSettings;


    uint8_t last_robot_id = 255;

public:
    DisplayController(BaseDisplayBoundary &displayBoundary, PMSVSettings &pmsvSettings);

    /**
     * Update checks if any values displayed have changed, and refreshes the display
     */
    void update();

    /**
     * Refresh the display
     */
    void display();
};