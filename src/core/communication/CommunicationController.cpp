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

#include <core/communication/CommunicationController.hpp>

BaseCommandController *CommunicationController::getCommandController(const Command &cmd) {
    for (size_t index = 0; index < commandControllerCount; index++) {
        auto &controller = commandControllers[index].get();
        if(controller.getCategoryID() == cmd.category_id) {
            return &controller;
        }
    }
    return nullptr;
}

void CommunicationController::handleQueuedCommand() {
    if (!commandQueue.empty()) {
        const auto &command = commandQueue.front();

        auto *commandController = getCommandController(command);

        commandQueue.pop();

        Response initialResponse = commandController->handle(
                command,
                [this, command](Response &msg) {
                    msg.message_id = command.message_id;
                    communicationBoundary.sendMessage(msg);
                }
        );
        if(initialResponse.successCode != SuccessCode::NO_RESPONSE) {
            communicationBoundary.sendMessage(initialResponse);
        }
    }
}

void CommunicationController::queueReceivedCommands() {
    while (communicationBoundary.isMessageAvailable()) {
        Command cmd = communicationBoundary.getNextMessage();

        // Check if the command was read correctly
        if(!cmd.isCorrectlyParsed()) {
            communicationBoundary.sendMessage(Response(cmd.message_id, SuccessCode::COMMAND_PARSE_ERROR));
            continue;
        }

        auto *commandController = getCommandController(cmd);

        // Check if an associated command controller was found for the command's category
        if(commandController == nullptr) {
            communicationBoundary.sendMessage(Response(cmd.message_id, SuccessCode::UNKOWN_COMMAND_CATEGORY));
            continue;
        }

        auto command_parameter_limits = commandController->getParameterLimits(cmd.command_id);

        // Check if the command controller knows the command
        if(command_parameter_limits.first == 255 && command_parameter_limits.second == 255) {
            communicationBoundary.sendMessage(Response(cmd.message_id, SuccessCode::UNKNOWN_COMMAND));
            continue;
        }

        // Check if the amount of parameters are correct
        if (cmd.parameter_length < command_parameter_limits.first || cmd.parameter_length > command_parameter_limits.second) {
            communicationBoundary.sendMessage(Response(cmd.message_id, SuccessCode::BAD_PARAMETERS));
            continue;
        }

        commandQueue.push(cmd);

    }
}

void CommunicationController::update() {
    queueReceivedCommands();
    handleQueuedCommand();
}
