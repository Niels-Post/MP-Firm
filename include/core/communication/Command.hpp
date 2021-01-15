/*
 * Copyright (c) 2021. Niels Post. AI Lab Vrije Universiteit Brussel.
 *
 * This file is part of MP-Firm.
 *
 * MP-Firm is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * MP-Firm is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with MP-Firm.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once


#include <cstddef>
#include <cstdint>

#include <core/util/ArduinoSafe.hpp>

static const size_t COMMAND_MAX_PARAM_LENGTH = 5;

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
    /// The byte count of the parameters stored in "parameters"
    size_t  parameter_length;
    /// All parameter bytes given for this command
    uint8_t parameters[COMMAND_MAX_PARAM_LENGTH];


    Command();

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
    static Command parse(uint8_t *data, const uint8_t &len = 0);

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

    /**
     * Check if the command was validly parsed.
     *
     * Note that this does not mean that the command itself is valid. Just that the parsing succeeded
     * @return
     */
    bool isCorrectlyParsed() const;

    /**
     * Print the data in this command
     */
    void print() const {
        Serial.println("---command---");
        Serial.print("Category: ");
        Serial.println(category_id);
        Serial.print("Command: ");
        Serial.println(command_id);
        Serial.print("Message: ");
        Serial.println(message_id);
        Serial.println("----------------");
    }


};
