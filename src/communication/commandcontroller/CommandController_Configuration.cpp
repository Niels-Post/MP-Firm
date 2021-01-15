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

#include <communication/commandcontroller/CommandController_Configuration.hpp>
#include <communication/CommandRegistry.hpp>
#include <cstring>

Response
CommandController_Configuration::handle(const Command &cmd, ResponseCallback callback) {
    switch (static_cast<ConfigurationCommand>(cmd.command_id)) {
        case SET_VALUE: {
            auto id = cmd.parameters[0];
            for (size_t i = 0; i < configuration_value_count; i++) {
                if (configurationValues[i].get().getId() == id) {
                    configurationValues[i].get().set((void *) (&cmd.parameters[1]));
                }
            }
            return Response{cmd.message_id, SuccessCode::SUCCESS};
            break;
        }
        case GET_VALUE: {
            auto id = cmd.parameters[0];
            for (size_t i = 0; i < configuration_value_count; i++) {
                if (configurationValues[i].get().getId() == id) {
                    auto data = configurationValues[i].get().get();
                    return Response{cmd.message_id, SuccessCode::SUCCESS, data.second, (uint8_t *) data.first};
                }
            }
            return Response{cmd.message_id, SuccessCode::BAD_PARAMETERS};
            break;
        }
        case LOAD:
            for (size_t i = 0; i < configuration_value_count; i++) {
                configurationValues[i].get().load();
            }
            break;
        case STORE:
            for (size_t i = 0; i < configuration_value_count; i++) {
                configurationValues[i].get().store();
            }
            break;
        case PRINT_ALL:
            for (size_t i = 0; i < configuration_value_count; i++) {
                configurationValues[i].get().print_info();
            }

            break;
        case GET_INFO: {
            auto configurationId = cmd.parameters[0];

            for(size_t i = 0; i <configuration_value_count; i++) {
                if(configurationValues[i].get().getId() == configurationId) {
                    const char *name = configurationValues[i].get().get_name();
                    uint8_t data_size = strlen(name ) + 1;
                    uint8_t data[data_size];
                    data[0] = configurationValues[i].get().getType();
                    std::memcpy(&data[1], name, data_size-1);
                    return Response{cmd.message_id, SuccessCode::SUCCESS, data_size, data};
                }
            }
            return Response{cmd.message_id, SuccessCode::BAD_PARAMETERS};


            break;
        }
        case GET_CONFIGURATION_COUNT:
            return Response{cmd.message_id, SuccessCode::SUCCESS, 4, (uint8_t *) &configuration_value_count};
            break;
        default:
        break;
    }
    return Response{cmd.message_id, SuccessCode::UNKNOWN_COMMAND};

}

uint8_t CommandController_Configuration::getCategoryID() {
    return static_cast<uint8_t>(CommandCategory::CONFIGURATION);
}

std::pair<uint8_t, uint8_t> CommandController_Configuration::getParameterLimits(uint8_t command_id) {
    switch (static_cast<ConfigurationCommand>(command_id)) {
        case SET_VALUE:
            return {1, 5};
        case GET_VALUE:
            return {1, 1};
        case LOAD:
        case STORE:
        case PRINT_ALL:
            return {0, 0};
        case GET_INFO:
            return {1, 1};
        case GET_CONFIGURATION_COUNT:
            return {0, 0};
        default:
            return {255, 255};

    }
}


CommandController_Configuration::CommandController_Configuration(
        std::reference_wrapper<BaseConfigurationValue> *configurationValues,
        size_t configurationValueCount) : configurationValues(
        configurationValues), configuration_value_count(configurationValueCount) {
    bool isFirstRun = BaseConfigurationValue::isFirstRun();
    for (size_t i = 0; i < configuration_value_count; i++) {
        if (isFirstRun) {
            configurationValues[i].get().store();
        } else {
            configurationValues[i].get().load();
        }
    }

    if (isFirstRun) {
        BaseConfigurationValue::removeFirstRun();
    }

}


