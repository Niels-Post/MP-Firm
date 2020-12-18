
#include <Arduino.h>
#include <controller/MovementController.hpp>
#include <entity/PMSVSettings.hpp>


SuccessCode MovementController::setSpeed(uint16_t speed) {
    if(leftMotor.isMoving() || rightMotor.isMoving()) {
        return SuccessCode::ROBOT_BUSY;
    }
    Serial.print("Speed set to: ");
    Serial.println(speed);
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

SuccessCode MovementController::startMoveMM(uint16_t mm, std::function<void(RobotMessage &)> callback) {
    return tryMoveMM(mm, std::move(callback));
}

SuccessCode MovementController::startRotateDegrees(uint16_t degrees, bool rotate_direction,
                                                   std::function<void(RobotMessage &)> callback) {
    if (leftMotor.isMoving() || rightMotor.isMoving()) {
        return SuccessCode::ROBOT_BUSY;
    }

    leftMotor.setDirection(rotate_direction);
    rightMotor.setDirection(!rotate_direction);

    return tryMoveMM(degrees * settings.mm_distance_per_degree, std::move(callback));
}

SuccessCode MovementController::tryMoveMM(uint16_t mm, std::function<void(RobotMessage &)> callback) {
    if (leftMotor.isMoving() || rightMotor.isMoving()) {
        return SuccessCode::ROBOT_BUSY;
    }

    current_callback = std::move(callback);
    isCallbackEnabled = true;
    if (!leftMotor.startMoveMM(mm) || !rightMotor.startMoveMM(mm)) {
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
        RobotMessage message = RobotMessage{SuccessCode::SUCCESS, 0, nullptr};
        current_callback(message);
        isCallbackEnabled = false;
    }
}

MovementController::MovementController(MotorBoundary &leftMotor, MotorBoundary &rightMotor,
                                       const PMSVSettings &settings) : leftMotor(leftMotor), rightMotor(rightMotor),
                                                                       settings(settings) {}



