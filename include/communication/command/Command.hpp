#pragma once

#include <cstdint>
#include <cstdio>

enum class CommandCategory: uint8_t {
    GENERAL,
    ACTION,
    MOVEMENT
};

enum class GeneralCommand: uint8_t {
    SET_COMMUNICATION_ACTIVEMODE
};

enum class ActionCommand: uint8_t {
    CANCEL_MOVEMENT,
    START_MOVE_STEPS,
    START_MOVE_CM,
    START_ROTATE_DEGREES,
    SET_SPEED
};

enum class MeasurementCommand: uint8_t {
    GET_MEASUREMENT_RAW,
    GET_DISTANCE_SENSOR
};

struct CommandData {
    uint8_t category_id;
    uint8_t command_id;
    uint8_t min_param_length;
    uint8_t max_param_length;
};

const CommandData commandDetails[] = {
        {0,0, 1,1},
        {1,0,0,0},
        {1,1,2,3},
        {1,2,2,3},
        {1,3,3,3},
        {1,4,1,1},
        {2,0,1,2},
        {2,1,1,2}
};

struct Command {

    uint8_t category_id;
    uint8_t command_id;
    uint8_t message_id;
    uint8_t parameters[30]; // TODO this could be handled better
    size_t parameter_length;

    /**
     * Create an empty message
     * @param categoryId The category (see CommandCategory)
     * @param commandId The command ID (see GeneralCommand, ActionCommand, MeasurementCommand)
     * @param messageId
     */
    Command(uint8_t categoryId, uint8_t commandId, uint8_t messageId);

    /**
     * Parse an array of bytes into a command
     * @param data Pointer to the start of the array
     * @param len Length of the array
     * @return
     */
    static Command parse(uint8_t *data, const uint8_t &len);

    /**
     * Check if an array of data is a properly formatted Command
     *
     * \details Checks if the size is correct for the given command.
     * Checks if the command given is known.
     * @param data
     * @param len
     * @return
     */
    static bool validate(const uint8_t * data, const uint8_t & len);

    uint16_t get_param16(const size_t &startIndex, bool msb_first = true) const;

    uint32_t get_param32(const size_t &startIndex, bool msb_first = true) const;
};
