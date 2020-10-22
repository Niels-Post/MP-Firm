#include <movement/MovementController.hpp>

#include <movement/MotorBoundary.hpp>

#include <Arduino.h>
#include <pmsv/PMSVSettings.hpp>

ReturnCode MovementController::setSpeed(uint16_t speed) {
    Serial.print("Speed set to: ");
    Serial.println(speed);
    return ReturnCode::BAD_PARAMETERS;
}

ReturnCode MovementController::setDirection(bool dir) {
    Serial.print("Direction set to: ");
    Serial.println(dir);
    return ReturnCode::BAD_PARAMETERS;
}

ReturnCode MovementController::startMoveCM(uint16_t cm) {
    Serial.print("Moving in cm:  ");
    Serial.println(cm);
    return ReturnCode::BAD_PARAMETERS;
}

ReturnCode MovementController::startMoveSteps(uint16_t steps) {
    Serial.print("Moving in steps: ");
    Serial.println(steps);
    return ReturnCode::BAD_PARAMETERS;
}

ReturnCode MovementController::startRotateDegrees(uint16_t degrees, bool direction) {
    Serial.print("Rotating: degrees: ");
    Serial.print(degrees);
    Serial.print(", direction: ");
    Serial.println(direction);
    return ReturnCode::BAD_PARAMETERS;
}

ReturnCode MovementController::halt() {
    Serial.println("Halting! ");
    return ReturnCode::BAD_PARAMETERS;
}

void MovementController::update() {
    leftMotor.update();
    rightMotor.update();
}

MovementController::MovementController(const PMSVSettings &pmsvSettings) : leftMotor(pmsvSettings.leftMotor.pin_enable,
                                                                                     pmsvSettings.leftMotor.pin_step,
                                                                                     pmsvSettings.leftMotor.pin_dir,
                                                                                     pmsvSettings.leftMotor.steps_per_mm),
                                                                           rightMotor(pmsvSettings.rightMotor.pin_enable,
                                                                                     pmsvSettings.rightMotor.pin_step,
                                                                                     pmsvSettings.rightMotor.pin_dir,
                                                                                     pmsvSettings.rightMotor.steps_per_mm){}
