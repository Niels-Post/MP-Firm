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

class BaseMotorBoundary {

public:
    /**
     * Stop all movement currently being processed
     */
    virtual void halt() = 0;

    /**
     * Update the movement currently being processed.
     * Depending on the implementation, this method may do nothing
     */
    virtual void update() = 0;

    /**
     * Change the direction this motor will rotate.
     *
     * Note: this should not change directions for movements that are already started
     * @param dir The new direction (true for forward, false for backward).
     */
    virtual void setDirection(bool dir) = 0;

    /**
     * Start a movement of a given number of degrees.
     *
     * The rotation here is rotation of the motorshaft/wheel itself, not the entire robot.
     * @param degrees Amount of degrees to move
     * @return True if the action was started successfully
     */
    virtual bool startMoveDegrees(uint16_t degrees) = 0;

    /**
     * Check if the motor is currently performing a movement
     * @return True if the motor is moving
     */
    virtual bool isMoving() = 0;

    /**
     * Set the max speed of this motor
     *
     * Depending on the implementation this could be applied mid-movement or not
     * @param max_speed_degrees_per_s The new max speed in degrees per second
     */
    virtual void setMaxSpeed(float max_speed_degrees_per_s) = 0;

};