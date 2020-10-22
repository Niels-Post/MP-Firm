#pragma once

#include <movement/MotorBoundary.hpp>
#include <communication/command/ReturnCommand.hpp>

class PMSVSettings;
class MovementController {
    MotorBoundary   leftMotor;
    MotorBoundary rightMotor;

public:
    ReturnCode setSpeed(uint16_t speed);

    ReturnCode setDirection(bool dir);

    ReturnCode startMoveCM(uint16_t cm);

    ReturnCode startMoveSteps(uint16_t steps);

    ReturnCode startRotateDegrees(uint16_t degrees, bool direction);

    ReturnCode halt();

    void update();

    MovementController(const PMSVSettings &pmsvSettings );
};