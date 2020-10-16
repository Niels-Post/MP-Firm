#pragma once

#include <cstdint>


class MotorController {
public:
    bool startMoveSteps(uint16_t steps) {
        return false;
    }

    void halt() {

    }
};