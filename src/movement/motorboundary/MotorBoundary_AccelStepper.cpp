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

#include <movement/motorboundary/MotorBoundary_AccelStepper.hpp>

void MotorBoundary_AccelStepper::halt() {
    stepper.stop();
    stepper.disableOutputs();
}

void MotorBoundary_AccelStepper::update() {
    if (stepper.distanceToGo() != 0) {
        stepper.run();
    } else {
        stepper.disableOutputs();
    }
}

MotorBoundary_AccelStepper::MotorBoundary_AccelStepper(AccelStepperConfig &_config)
        : config(_config), stepper(stepper.DRIVER,
                  config.pin_step, config.pin_dir) {
    stepper.setEnablePin(config.pin_enable);
    stepper.setPinsInverted(false, false, true);

    pinMode(config.pin_ms1, OUTPUT);
    digitalWrite(config.pin_ms1, LOW);
    pinMode(config.pin_ms2, OUTPUT);
    digitalWrite(config.pin_ms2, LOW);
}

void MotorBoundary_AccelStepper::setDirection(bool dir) {
    rotateDirection = dir ^ !config.forward_direction;
}

bool MotorBoundary_AccelStepper::startMoveDegrees(uint16_t degree) {
    long stepsToMove = degree * config.steps_per_degree;
    if (!rotateDirection) {
        stepsToMove *= -1;
    }
    stepper.move(stepsToMove);
    stepper.enableOutputs();
    return true;

}

bool MotorBoundary_AccelStepper::isMoving() {
    return stepper.distanceToGo() != 0;
}

void MotorBoundary_AccelStepper::setMaxSpeed(float max_degrees_per_second) {
    stepper.setMaxSpeed(max_degrees_per_second * config.steps_per_degree * 10);
    stepper.setAcceleration(max_degrees_per_second * config.steps_per_degree);
}


