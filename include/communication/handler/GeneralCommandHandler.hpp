#pragma once

#include <communication/handler/CommandHandler.hpp>

/**
 * Handles commands in the category \refitem{CommandCategory::GENERAL}
 */
class GeneralCommandHandler : public CommandHandler {
public:
    /**
     * Handle a General Command
     * @param cmd Command to handle
     * @return The result of the command. This should be sent back to the sender of the command
     */
    ReturnCommand handle(const Command &cmd) override;

};
