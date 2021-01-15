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

/**
 * Available categories for wireless commands
 */
enum class CommandCategory : uint8_t {
    GENERAL = 0,
    ACTION = 1,
    MEASUREMENT = 2,
    CONFIGURATION = 3
};

/**
 * Commands in the "General" category
 */
enum GeneralCommand {
    REBOOT = 0,
    SET_ID = 1
};

/**
 * Commands in the "Action" category
 */
enum ActionCommand {
    CANCEL_MOVEMENT = 0,
    START_MOVE_MM = 1,
    START_ROTATE_DEGREES = 2,
    SET_SPEED = 3
};

/**
 * Commands in the "Measurement" category
 */
enum MeasurementCommand {
    GET_MEASUREMENT_RAW,
    GET_DISTANCE_SENSOR
};

/**
 * Commands in the "Flash" category
 */
enum ConfigurationCommand {
    SET_VALUE,
    GET_VALUE,
    LOAD,
    STORE,
    PRINT_ALL,
    GET_INFO,
    GET_CONFIGURATION_COUNT,
};