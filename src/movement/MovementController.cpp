#include <movement/MovementController.hpp>

#include <movement/MotorController.hpp>

#include <Arduino.h>

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

}
