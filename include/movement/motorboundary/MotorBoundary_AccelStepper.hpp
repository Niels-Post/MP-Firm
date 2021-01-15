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

#include <movement/motorboundary/AccelStepperConfig.hpp>

#include <core/movement/BaseMotorBoundary.hpp>

#include <AccelStepper.h>

/**
 * A motorboundary used for a single Stepper Motor.
 *
 * Uses the Arduino AccelStepper library
 */
class MotorBoundary_AccelStepper: public BaseMotorBoundary {
    /// Configuration object for the AccelStepper
    AccelStepperConfig &config;
    /// Stepper motor object that is used to move the motor
    AccelStepper stepper;
    /// The current rotation direction
    bool     rotateDirection  = true;
public:
    /**
     * Create a motorboundary
     *
     * The constructor automatically creates the underlying AccelStepper object
     * @param _config The Configuration settings used for the motor
     */
    MotorBoundary_AccelStepper(AccelStepperConfig &_config);

    /**
     * \copydoc MotorBoundary::startMoveDegrees(uint16_t)
     */
    bool startMoveDegrees(uint16_t mm) override;

    /**
     * \copydoc MotorBoundary::halt()
     */
    void halt() override;

    /**
     * \copydoc MotorBoundary::update()
     */
    void update() override;

    /**
     * \copydoc MotorBoundary::setDirection(boolwsl)
     */
    void setDirection(bool dir) override;

    /**
     * Check if this motor is currently moving
     * @return True if the robot is still moving
     */
    bool isMoving() override;

    /**
     * Set the max speed the motor can rotate in in degrees per second
     * @param max_degrees_per_second
     */
    void setMaxSpeed(float max_degrees_per_second) override;


};