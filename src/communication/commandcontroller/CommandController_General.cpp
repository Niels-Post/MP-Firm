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

#include <communication/commandcontroller/CommandController_General.hpp>
#include <communication/CommandRegistry.hpp>


Response CommandController_General::handle(const Command &cmd, ResponseCallback callback) {
    auto cmd_id = static_cast<GeneralCommand>(cmd.command_id);
    switch(cmd_id) {
        case REBOOT:
            rstc_start_software_reset(RSTC);
            break;
        case SET_ID:
            if(pmsvSettings.robot_id != 0) {
                if(pmsvSettings.robot_id == cmd.parameters[0]) {
                    return {cmd.message_id, SuccessCode::ID_ALREADY_SET, 0, nullptr, true};
                }
                return {cmd.message_id, SuccessCode::NO_RESPONSE};
            }
            pmsvSettings.robot_id = cmd.parameters[0];
            configRobotId.store();
            Response res{cmd.message_id, SuccessCode::SUCCESS, 0, nullptr, true};
            callback(res);
            rstc_start_software_reset(RSTC);
    }
    return {cmd.message_id, SuccessCode::UNKNOWN_COMMAND};
}

uint8_t CommandController_General::getCategoryID() {
    return 0;
}

CommandController_General::CommandController_General(PMSVSettings &settings, ConfigurationValue<uint8_t> &robotIdConfig)
        : pmsvSettings{settings}, configRobotId{robotIdConfig} {}

std::pair<uint8_t, uint8_t> CommandController_General::getParameterLimits(uint8_t command_id) {
    auto cmd_id = static_cast<GeneralCommand>(command_id);

    switch (cmd_id) {
        case REBOOT:
            return {0, 0};
        case SET_ID:
            return {1, 1};
        default:
            return {255, 255};

    }
}
