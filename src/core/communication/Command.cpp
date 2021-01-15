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

#include <core/communication/Command.hpp>



Command Command::parse(uint8_t *data, const uint8_t &len) {
    if (len < 2) {
        return Command{};
    }

    Command c(data[0] >> 5u, data[0] & 0x1Fu, data[1]);

    c.parameter_length = len - 2;

    for (size_t i = 0; i < c.parameter_length; i++) {
        c.parameters[i] = data[i + 2];
    }

    for (size_t i = c.parameter_length; i < COMMAND_MAX_PARAM_LENGTH; i++) {
        c.parameters[i] = 0;
    }

    return c;
}

Command::Command(uint8_t categoryId, uint8_t commandId, uint8_t messageId) : category_id(categoryId),
                                                                             command_id(commandId),
                                                                             message_id(messageId) {}

uint16_t Command::get_param16(const size_t &startIndex, bool msb_first) const {
    if (msb_first) {
        return (parameters[0] << 8) | parameters[1];
    } else {
        return (parameters[1] << 8) | parameters[0];
    }
}

uint32_t Command::get_param32(const size_t &startIndex, bool msb_first) const {
    if (msb_first) {
        return (parameters[0] << 24) | (parameters[1] << 24) | (parameters[2] << 24) | parameters[3];
    } else {
        return (parameters[3] << 24) | (parameters[2] << 24) | (parameters[1] << 24) | parameters[0];
    }
}

Command::Command(): category_id(255), command_id(255), message_id(255),  parameter_length(255), parameters{255}  {}

bool Command::isCorrectlyParsed() const {
    return (category_id != 255 || command_id != 255 || message_id != 255);
}
