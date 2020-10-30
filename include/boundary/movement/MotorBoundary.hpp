#pragma once

#include <cstdint>

class MotorBoundary{

public:
    virtual void halt() = 0;

    virtual void update() = 0;

    virtual void setDirection(bool dir) = 0;

    virtual bool startMoveMM(uint16_t mm) = 0;
};