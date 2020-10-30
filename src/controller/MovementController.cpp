
#include <Arduino.h>
#include <controller/MovementController.hpp>
#include <entity/PMSVSettings.hpp>



SuccessCode MovementController::setSpeed(uint16_t speed) {
    Serial.print("Speed set to: ");
    Serial.println(speed);
    return SuccessCode::BAD_PARAMETERS;
}

SuccessCode MovementController::setDirection(bool dir) {
    Serial.print("Direction set to: ");
    Serial.println(dir);
    leftMotor.setDirection(dir);
    rightMotor.setDirection(dir);
    return SuccessCode::BAD_PARAMETERS;
}

SuccessCode MovementController::startMoveMM(uint16_t mm) {
    return tryMoveMM(mm);
}

SuccessCode MovementController::startRotateDegrees(uint16_t degrees, bool rotate_direction) {
    leftMotor.setDirection(rotate_direction);
    rightMotor.setDirection(!rotate_direction);

    return tryMoveMM(degrees * settings.degrees_per_mm_distance);
}

SuccessCode MovementController::tryMoveMM(uint16_t mm) const {
    if(leftMotor.startMoveMM(mm) &&
       rightMotor.startMoveMM(mm)) {
        return SuccessCode::SUCCESS;
    } else {
        return SuccessCode::HARDWARE_ERROR;
    }
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
}

MovementController::MovementController(MotorBoundary &leftMotor, MotorBoundary &rightMotor,
                                       const PMSVSettings &settings) : leftMotor(leftMotor), rightMotor(rightMotor),
                                                                       settings(settings) {}



