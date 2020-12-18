#pragma once

#include <cstdint>
#include <cstdio>
#include <utility>
#include <entity/CommandData.hpp>
#include <Arduino.h>
#undef min
#undef max

static const size_t COMMAND_MAX_PARAM_LENGTH = 5;

/**
 * A struct containing a command received by the robot.
 */
struct ControllerMessage {
    /// The category id of the command (see the information sheet)
    uint8_t category_id;
    /// The command id of the command (see the information sheet)
    uint8_t command_id;
    /// A value for identifying a specific message.
    uint8_t message_id;
    /// The byte count of the parameters stored in "parameters"
    size_t  parameter_length;
    /// All parameter bytes given for this command
    uint8_t parameters[COMMAND_MAX_PARAM_LENGTH];


    ControllerMessage();

    /**
     * Create an empty message
     * @param categoryId The category (see CommandCategory)
     * @param commandId The command ID (see GeneralCommand, ActionCommand, MeasurementCommand)
     * @param messageId
     */
    ControllerMessage(uint8_t categoryId, uint8_t commandId, uint8_t messageId);

    /**
     * Parse an array of bytes into a command
     * @param data Pointer to the start of the array
     * @param len Length of the array
     * @return
     */
    static ControllerMessage parse(uint8_t *data, const uint8_t &len = 0);

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

    bool isValid() const;

    static size_t maxMessageSize() {
        return COMMAND_MAX_PARAM_LENGTH + 3;
    }

    void print() const {
        Serial.println("---message---");
        Serial.print("Category: ");
        Serial.println(category_id);
        Serial.print("Command: ");
        Serial.println(command_id);
        Serial.print("Message: ");
        Serial.println(message_id);
        Serial.println("----------------");
    }


};
