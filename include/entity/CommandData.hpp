#pragma once

/**
 * Available categories for wireless commands
 */
enum class CommandCategory : uint8_t {
    GENERAL     = 0,
    ACTION      = 1,
    MEASUREMENT = 2
};

/**
 * Commands in the "General" category
 */
enum GeneralCommand {
    SET_COMMUNICATION_ACTIVEMODE = 0
};

/**
 * Commands in the "Action" category
 */
enum ActionCommand {
    CANCEL_MOVEMENT      = 0,
    START_MOVE_MM        = 1,
    START_ROTATE_DEGREES = 2,
    SET_SPEED            = 3
};

/**
 * Commands in the "Measurement" category
 */
enum MeasurementCommand {
    GET_MEASUREMENT_RAW,
    GET_DISTANCE_SENSOR
};