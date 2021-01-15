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

#include <core/display/DisplayController.hpp>
#include <cstdio>

DisplayController::DisplayController(BaseDisplayBoundary &displayBoundary, PMSVSettings &pmsvSettings)
        : displayBoundary(displayBoundary), pmsvSettings(pmsvSettings) {}

void DisplayController::update() {
    bool dirty = false;
    if (last_robot_id != pmsvSettings.robot_id) {
        dirty = true;
        last_robot_id = pmsvSettings.robot_id;
    }


    if (dirty) {
        display();
    }
    displayBoundary.update();
}

void DisplayController::display() {
    displayBoundary.clear();

    auto robot_id = (char *) "Robot ID:";
    char numberstring[4];
    sprintf(numberstring, "%d", static_cast<int>(pmsvSettings.robot_id));

    displayBoundary.write(robot_id);
    displayBoundary.write(numberstring);
    displayBoundary.newline();

}
