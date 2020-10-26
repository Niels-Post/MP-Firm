#include <movement/MovementController.hpp>

#include <movement/MotorBoundary.hpp>

#include <Arduino.h>
#include <pmsv/PMSVSettings.hpp>

ReturnCode MovementController::tryMoveSteps(long steps) {
    if (!leftMotor.startMoveSteps(steps) ||
        !rightMotor.startMoveSteps(steps)) {
        return ReturnCode::HARDWARE_ERROR;
    }
    return ReturnCode::SUCCESS;
}


ReturnCode MovementController::setSpeed(uint16_t speed) {
    Serial.print("Speed set to: ");
    Serial.println(speed);
    return ReturnCode::BAD_PARAMETERS;
}

ReturnCode MovementController::setDirection(bool dir) {
    Serial.print("Direction set to: ");
    Serial.println(dir);
    leftMotor.setDirection(dir);
    rightMotor.setDirection(dir);
    return ReturnCode::BAD_PARAMETERS;
}

ReturnCode MovementController::startMoveCM(uint16_t cm) {
    const long &stepsToMove = settings.steps_per_cm * cm;
    return tryMoveSteps(stepsToMove);
}

ReturnCode MovementController::startMoveSteps(uint16_t steps) {
    return tryMoveSteps(steps);
}

ReturnCode MovementController::startRotateDegrees(uint16_t degrees, bool rotate_direction) {
    leftMotor.setDirection(rotate_direction);
    rightMotor.setDirection(!rotate_direction);

    const long &stepsToMove = settings.steps_per_degree * degrees;
    return tryMoveSteps(stepsToMove);
}

ReturnCode MovementController::startRotateSteps(uint16_t steps, bool rotate_direction) {
    leftMotor.setDirection(rotate_direction);
    rightMotor.setDirection(!rotate_direction);

    return tryMoveSteps(steps);
}

ReturnCode MovementController::halt() {
    Serial.println("Halting! ");
    leftMotor.halt();
    rightMotor.halt();
    return ReturnCode::SUCCESS;
}

void MovementController::update() {
    leftMotor.update();
    rightMotor.update();
}

MovementController::MovementController(const PMSVSettings &pmsvSettings) : leftMotor(pmsvSettings.leftMotor.pin_enable,
                                                                                     pmsvSettings.leftMotor.pin_step,
                                                                                     pmsvSettings.leftMotor.pin_dir,
                                                                                     pmsvSettings.leftMotor.steps_per_mm),
                                                                           rightMotor(
                                                                                   pmsvSettings.rightMotor.pin_enable,
                                                                                   pmsvSettings.rightMotor.pin_step,
                                                                                   pmsvSettings.rightMotor.pin_dir,
                                                                                   pmsvSettings.rightMotor.steps_per_mm),
                                                                           settings(pmsvSettings) {}



