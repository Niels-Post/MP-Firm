#pragma once

#include <controller/CommandCategoryController.hpp>
#include <entity/RobotMessage.hpp>
#include <entity/ControllerMessage.hpp>

class MovementController;


/**
 * Handles commands in the category \refitem{CommandCategory::ACTION}
 */
class ActionCommandController : public CommandCategoryController {
    /// MovementController, used for performing movement actions
    MovementController &movementController;
public:
    /**
     * Handle an ActionCommand
     * @param cmd Command to handle
     * @return The result of the action. This should be sent back to the sender of the command
     */
    RobotMessage handle(const ControllerMessage &cmd, std::function<void(RobotMessage &)> callback) override;

    /**
     * Construct the ActionCommandHandler
     * @param movementController The robot's movementController
     */
    ActionCommandController(MovementController &movementController);


    uint8_t getCategoryID() override;

    std::pair<uint8_t, uint8_t> getParameterLimits(uint8_t command_id) override;
};
