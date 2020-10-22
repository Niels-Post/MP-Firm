#pragma once

#include <communication/handler/CommandHandler.hpp>

class MovementController;


/**
 * Handles commands in the category \refitem{CommandCategory::ACTION}
 */
class ActionCommandHandler : public CommandHandler {
    /// MovementController, used for performing movement actions
    MovementController &movementController;
public:
    /**
     * Handle an ActionCommand
     * @param cmd Command to handle
     * @return The result of the action. This should be sent back to the sender of the command
     */
    ReturnCommand handle(const Command &cmd) override;

    /**
     * Construct the ActionCommandHandler
     * @param movementController The robot's movementController
     */
    ActionCommandHandler(MovementController &movementController);
};
