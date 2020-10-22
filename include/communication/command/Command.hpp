#pragma once

#include <cstdint>
#include <cstdio>
#include <utility>


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
enum class GeneralCommand : uint8_t {
    SET_COMMUNICATION_ACTIVEMODE = 0
};

/**
 * Commands in the "Action" category
 */
enum class ActionCommand : uint8_t {
    CANCEL_MOVEMENT      = 0,
    START_MOVE_STEPS     = 1,
    START_MOVE_CM        = 2,
    START_ROTATE_DEGREES = 3,
    SET_SPEED            = 4
};

/**
 * Commands in the "Measurement" category
 */
enum class MeasurementCommand : uint8_t {
    GET_MEASUREMENT_RAW,
    GET_DISTANCE_SENSOR
};






/**
 * A struct containing a command received by the robot.
 */
struct Command {
    /// The category id of the command (see the information sheet)
    uint8_t category_id;
    /// The command id of the command (see the information sheet)
    uint8_t command_id;
    /// A value for identifying a specific message.
    uint8_t message_id;

    /// All parameter bytes given for this command
    uint8_t parameters[5];
    /// The byte count of the parameters stored in "parameters"
    size_t  parameter_length;

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
    static bool validate(const uint8_t *data, const uint8_t &len);

    /**
     * Get the minimum and maximum parameter length for a given command.
     *
     * @param cat The Command Category id
     * @param cmd The command ID
     * @return A pair of sizes, where first is the minimum size, and second is the maximum size
     */
    static std::pair<uint8_t, uint8_t> getParameterLimits(CommandCategory cat, uint8_t cmd);

    /**
     * Get a 16 bit unsigned integer from the parameters
     * @param startIndex Parameter index at which the value starts
     * @param msb_first Wether the byte order is msb first (true, default) or lsbyte first(false)
     * @return The requested value
     */
    uint16_t get_param16(const size_t &startIndex, bool msb_first = true) const;

    /**
     * Get a 32 bit unsigned integer from the parameters
     * @param startIndex Parameter index at which the value starts
     * @param msb_first Wether the byte order is msb first (true, default) or lsbyte first(false)
     * @return The requested value
     */
    uint32_t get_param32(const size_t &startIndex, bool msb_first = true) const;
};
