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
 * Configuration parameters for an AccelStepper motor.
 *
 * For more information about pins and settings, refer to the link below
 * https://www.trinamic.com/fileadmin/assets/Products/ICs_Documents/TMC2209_Datasheet_V103.pdf
 * (Only tested with a TMC2209 driver)
 */
struct AccelStepperConfig {
    /// Pin 1 for Microstepping
    uint8_t pin_ms1;
    /// Pin 2 for microsftepping
    uint8_t pin_ms2;
    /// Enable pin for the driver
    uint8_t pin_enable;
    /// Step pin for the driver
    uint8_t pin_step;
    /// Direction pin for the driver
    uint8_t pin_dir;
    /// The amount of steps for a single degree of movement (depends on the motor used)
    float steps_per_degree;
    /// Which direction is forward (depends on how the motor is connected+rotated)
    bool forward_direction;
};