//
// Created by Niels on 16/10/2020.
//

#include <communication/command/Command.hpp>
#include <Arduino.h>


Command Command::parse(uint8_t *data, const uint8_t &len) {
    Command c(data[0] >> 5u, data[0] & 0x1Fu, data[2]);

    c.parameter_length = len - 2;

    for(size_t i = 0; i < c.parameter_length; i++) {
        c.parameters[i] = data[i+2];
    }

    for(size_t i = c.parameter_length; i < 30; i++) {
        c.parameters[i] = 0;
    }

    return c;
}

bool Command::validate(const uint8_t *data, const uint8_t &len) {
    if(len < 2) {
        Serial.println("toto short");
        return false;
    }

    uint8_t cat = data[0] >> 5u;
    uint8_t cmd = data[0] & 0x1Fu;
    uint8_t param_length = len - 2;

    for(const CommandData & details : commandDetails) {
        if(details.category_id == cat &&
           details.command_id == cmd) {
            Serial.println("Command found");
            if(param_length >= details.min_param_length && param_length <= details.max_param_length) {
                Serial.println("Good boy command");
                return true;
            }
        }
    }
    return false;
}

Command::Command(uint8_t categoryId, uint8_t commandId, uint8_t messageId) : category_id(categoryId),
                                                                             command_id(commandId),
                                                                             message_id(messageId) {}

uint16_t Command::get_param16(const size_t &startIndex, bool msb_first) const {
    if(msb_first) {
        return (parameters[0] << 8) | parameters[1];
    } else {
        return (parameters[1] << 8) | parameters[0];
    }
}

uint32_t Command::get_param32(const size_t &startIndex, bool msb_first) const {
    if(msb_first) {
        return (parameters[0] << 24) | (parameters[1] << 24) |  (parameters[2] << 24) | parameters[3];
    } else {
        return (parameters[3] << 24) | (parameters[2] << 24) |  (parameters[1] << 24) | parameters[0];
    }
}
