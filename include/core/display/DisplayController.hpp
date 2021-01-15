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