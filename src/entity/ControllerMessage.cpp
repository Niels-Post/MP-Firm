//
// Created by Niels on 16/10/2020.
//

#include <entity/ControllerMessage.hpp>
#include <Arduino.h>


ControllerMessage ControllerMessage::parse(uint8_t *data, const uint8_t &len) {
    if (len < 3) {
        return ControllerMessage{};
    }



    ControllerMessage c(data[0] >> 5u, data[0] & 0x1Fu, data[1]);

    c.parameter_length = len - 2;

    for (size_t i = 0; i < c.parameter_length; i++) {
        c.parameters[i] = data[i + 2];
    }

    for (size_t i = c.parameter_length; i < COMMAND_MAX_PARAM_LENGTH; i++) {
        c.parameters[i] = 0;
    }

    return c;
}

ControllerMessage::ControllerMessage(uint8_t categoryId, uint8_t commandId, uint8_t messageId) : category_id(categoryId),
                                                                                                 command_id(commandId),
                                                                                                 message_id(messageId) {}

uint16_t ControllerMessage::get_param16(const size_t &startIndex, bool msb_first) const {
    if (msb_first) {
        return (parameters[0] << 8) | parameters[1];
    } else {
        return (parameters[1] << 8) | parameters[0];
    }
}

uint32_t ControllerMessage::get_param32(const size_t &startIndex, bool msb_first) const {
    if (msb_first) {
        return (parameters[0] << 24) | (parameters[1] << 24) | (parameters[2] << 24) | parameters[3];
    } else {
        return (parameters[3] << 24) | (parameters[2] << 24) | (parameters[1] << 24) | parameters[0];
    }
}

ControllerMessage::ControllerMessage(): category_id(255), command_id(255), message_id(255), parameters{255}, parameter_length(255)  {}

bool ControllerMessage::isValid() const {
    return (category_id != 255 || command_id != 255 || message_id != 255);
}
