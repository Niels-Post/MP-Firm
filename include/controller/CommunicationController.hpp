#pragma once

#include <RF24.h>

#include <entity/StackQueue.hpp>
#include <boundary/communication/CommandBoundary.hpp>
#include "CommandCategoryController.hpp"

class PMSVSettings;


class RobotMessage;


template <class T, std::size_t N>
constexpr std::size_t array_size(const T (&array)[N]) noexcept
{
    return N;
}

/**
 * Controller for the wireless communication aspect of the robot.
 *
 * This controller continuously checks for received RF24 Commands, parses them, and invokes a \refitem{CommandHandler} for them.
 * The controller then transmits the ReturnCode from the handler to the sender of the command
 */

template<size_t commandQueueMaxLength, size_t handlerCount>
class CommunicationController {
private:
    CommandBoundary                                       &commandBoundary;
    /// Queue of commands that are still to be handled
    StackQueue <ControllerMessage, commandQueueMaxLength> commandQueue;
    ///
    CommandCategoryController                             *commandCategoryHandlers[handlerCount];


protected:
    /**
     * Retrieve the next command from the queue, and handle it.
     */
    void handleQueuedCommand() {
        if (!commandQueue.empty()) {
            const auto                     &command = commandQueue.front();
            for (CommandCategoryController *handler: commandCategoryHandlers) {
                if (command.category_id == handler->getCategoryID()) {
                    commandBoundary.sendMessage(handler->handle(command));
                    commandQueue.pop();
                    return;
                }
            }

            Serial.println("Command category not recognized");
        }
    }

    /**
     * If data is available on RF24, try to parse the data as command, and add it to the commandQueue
     *
     * When no data is available, this function returns
     * When a command is inproperly formatted, the function automatically transmits the error code BAD_PARAMETERS to the sender
     */
    void parseNextCommand() {
        if (commandBoundary.isMessageAvailable()) {
            ControllerMessage cmd = commandBoundary.getNextMessage();
            if (cmd.isValid()) {
                commandQueue.push(cmd);
            }
        }
    }

public:
    CommunicationController(CommandBoundary &commandBoundary,
                            CommandCategoryController *commandCatHandlers[handlerCount])
            : commandBoundary(commandBoundary), commandQueue() {
        for (size_t i = 0; i < handlerCount; i++) {
            commandCategoryHandlers[i] = commandCatHandlers[i];
        }
    }


    /**
     * Check for received messages and handle them.
     */
    void update() {
        parseNextCommand();
        handleQueuedCommand();
    }


};

