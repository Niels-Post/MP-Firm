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


#include <core/movement/MovementController.hpp>


SuccessCode MovementController::setSpeed(float speed) {
    if(leftMotor.isMoving() || rightMotor.isMoving()) {
        return SuccessCode::ROBOT_BUSY;
    }
    leftMotor.setMaxSpeed(speed);
    rightMotor.setMaxSpeed(speed);
    return SuccessCode::SUCCESS;
}

SuccessCode MovementController::setDirection(bool dir) {
    if(leftMotor.isMoving() || rightMotor.isMoving()) {
        return SuccessCode::ROBOT_BUSY;
    }
    leftMotor.setDirection(dir);
    rightMotor.setDirection(dir);
    return SuccessCode::SUCCESS;
}

SuccessCode MovementController::startMoveMM(uint16_t mm, ResponseCallback callback) {
    return tryMoveMM(mm, std::move(callback));
}

SuccessCode MovementController::startRotateDegrees(uint16_t degrees, bool rotate_direction,
                                                   ResponseCallback callback) {
    if (leftMotor.isMoving() || rightMotor.isMoving()) {
        return SuccessCode::ROBOT_BUSY;
    }

    leftMotor.setDirection(rotate_direction);
    rightMotor.setDirection(!rotate_direction);

    return tryMoveMM(degrees * settings.mm_distance_per_robot_rotation_degree, std::move(callback));
}

SuccessCode MovementController::tryMoveMM(uint16_t mm, ResponseCallback callback) {
    if (leftMotor.isMoving() || rightMotor.isMoving()) {
        return SuccessCode::ROBOT_BUSY;
    }

    current_callback = std::move(callback);
    isCallbackEnabled = true;



    if (!leftMotor.startMoveDegrees(mm * settings.motor_rotation_degrees_per_mm_distance) || !rightMotor.startMoveDegrees(mm * settings.motor_rotation_degrees_per_mm_distance)) {
        return SuccessCode::HARDWARE_ERROR;
    }

    return SuccessCode::ACTION_STARTED;

}

SuccessCode MovementController::halt() {
    Serial.println("Halting! ");
    leftMotor.halt();
    rightMotor.halt();
    return SuccessCode::SUCCESS;
}

void MovementController::update() {
    leftMotor.update();
    rightMotor.update();

    if (isCallbackEnabled && !leftMotor.isMoving() && !rightMotor.isMoving()) {
        Response message = Response{SuccessCode::SUCCESS, 0, nullptr};
        current_callback(message);
        isCallbackEnabled = false;
    }
}

MovementController::MovementController(BaseMotorBoundary &leftMotor, BaseMotorBoundary &rightMotor,
                                       const PMSVSettings &settings) : leftMotor(leftMotor), rightMotor(rightMotor),
                                                                       settings(settings) {
    leftMotor.setMaxSpeed(settings.max_speed);
    rightMotor.setMaxSpeed(settings.max_speed);
}



