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

#include <cstdint>

struct PMSVSettings {
    /// Robot Identifier. Should be set through the Configuration Commands
    uint8_t robot_id;
    /// How many degrees do both motors need to rotate before the robot moves 1 mm
    float motor_rotation_degrees_per_mm_distance;
    /// How far do both wheels need to rotate in opposite direction before the robot rotates 1 degree
    float mm_distance_per_robot_rotation_degree;
    /// Minimum speed for the robot
    float min_speed;
    /// Maximum speed for the robot
    float max_speed;
};

