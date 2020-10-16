#pragma once

#include <cstdint>
#include <cstdio>

enum class ReturnCode : uint8_t {
    SUCCESS        = 0,
    ROBOT_BUSY     = 1,
    HARDWARE_ERROR = 2,
    MOTOR_STALL    = 3,
    BAD_PARAMETERS = 4,
    NO_SUCH_SENSOR = 5
};

struct ReturnCommand {
    uint8_t message_id;
    ReturnCode returnCode;
    uint8_t data[4];

    ReturnCommand(uint8_t messageId, ReturnCode returnCode, const uint8_t *dat);
};
