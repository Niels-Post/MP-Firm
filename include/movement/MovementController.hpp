#pragma once

#include <movement/MotorController.hpp>
#include <communication/command/ReturnCommand.hpp>

class MovementController {
    MotorController leftMotor;
    MotorController rightMotor;

public:
    ReturnCode setSpeed(uint16_t speed);
    ReturnCode setDirection(bool dir);
    ReturnCode startMoveCM(uint16_t cm);
    ReturnCode startMoveSteps(uint16_t steps);
    ReturnCode startRotateDegrees(uint16_t degrees, bool direction);
    ReturnCode halt();
    void update();
};