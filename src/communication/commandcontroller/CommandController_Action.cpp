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

#include <communication/commandcontroller/CommandController_Action.hpp>
#include <communication/CommandRegistry.hpp>

Response CommandController_Action::handle(const Command &cmd, ResponseCallback callback) {
    SuccessCode code = SuccessCode::BAD_PARAMETERS;
    switch (cmd.command_id) {
        case CANCEL_MOVEMENT:
            code = movementController.halt();
            break;
        case START_MOVE_MM: {
            if (cmd.parameter_length > 2) {
                movementController.setDirection(cmd.parameters[2]);
            }

            code = movementController.startMoveMM(cmd.get_param16(0), callback);
            break;
        }
        case START_ROTATE_DEGREES:
            code = movementController.startRotateDegrees(cmd.get_param16(0), cmd.parameters[2],
                                                         callback);

            break;
        case SET_SPEED:
            code = movementController.setSpeed(cmd.parameters[0]);
            break;
    }

    return {cmd.message_id, code};
}

CommandController_Action::CommandController_Action(MovementController &movementController) : movementController(
        movementController) {}

uint8_t CommandController_Action::getCategoryID() {
    return 1;
}

std::pair<uint8_t, uint8_t> CommandController_Action::getParameterLimits(uint8_t command_id) {
    switch (command_id) {
        case CANCEL_MOVEMENT:
            return {0, 0};
        case START_MOVE_MM:
            return {2, 3};
        case START_ROTATE_DEGREES:
            return {3, 3};;
        case SET_SPEED:
            return {1, 1};
        default:
            return {255, 255};
    }
}
