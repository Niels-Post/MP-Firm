#pragma once

#include <communication/command/Command.hpp>
#include <communication/command/ReturnCommand.hpp>

/**
  * Interface to handle commands in a specific category
 */
class CommandHandler {
public:
    /**
     * Handle a Command
     * @param cmd Command to handle
     * @return The result of the command. This should be sent back to the sender of the command
     */
    virtual ReturnCommand handle(const Command &cmd) = 0;
};
