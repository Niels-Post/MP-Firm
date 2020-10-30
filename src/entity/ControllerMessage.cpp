//
// Created by Niels on 16/10/2020.
//

#include <entity/ControllerMessage.hpp>
#include <Arduino.h>


ControllerMessage ControllerMessage::parse(uint8_t *data, const uint8_t &len) {
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

bool ControllerMessage::validate(const uint8_t *data, const uint8_t &len) {
    if (len < 2) {
        return false;
    }

    uint8_t cat          = data[0] >> 5u;
    uint8_t cmd          = data[0] & 0x1Fu;
    uint8_t param_length = len - 2;

    auto sizes = ControllerMessage::getParameterLimits(static_cast<CommandCategory>(cat), cmd);


    if (param_length >= sizes.first && param_length <= sizes.second) {
        return true;
    }

    return false;
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

std::pair<uint8_t, uint8_t> ControllerMessage::getParameterLimits(CommandCategory cat, uint8_t cmd) {

    switch (cat) {

        case CommandCategory::GENERAL: {
            switch (static_cast<GeneralCommand>(cmd)) {
                case GeneralCommand::SET_COMMUNICATION_ACTIVEMODE:
                    return {1, 1};
            }
            break;
        }


        case CommandCategory::ACTION: {
            switch (static_cast<ActionCommand>(cmd)) {
                case ActionCommand::CANCEL_MOVEMENT:
                    return {0, 0};
                case ActionCommand::START_MOVE_STEPS:
                case ActionCommand::START_MOVE_MM:
                    return {2, 3};
                case ActionCommand::START_ROTATE_DEGREES:
                    return {3, 3};
                case ActionCommand::START_ROTATE_STEPS:
                    return {3, 3};
                case ActionCommand::SET_SPEED:
                    return {1, 1};
            }
            break;
        }
        case CommandCategory::MEASUREMENT:
            switch (static_cast<MeasurementCommand>(cmd)) {
                case MeasurementCommand::GET_MEASUREMENT_RAW:
                case MeasurementCommand::GET_DISTANCE_SENSOR:
                    return {1, 2};
            }
            break;
    }

    return {255, 255};
}

ControllerMessage::ControllerMessage(): category_id(255), command_id(255), message_id(255), parameters{255}, parameter_length(255)  {}
