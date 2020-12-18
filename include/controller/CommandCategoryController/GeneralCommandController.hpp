#pragma once

#include <controller/CommandCategoryController.hpp>

/**
 * Handles commands in the category \refitem{CommandCategory::GENERAL}
 */
class GeneralCommandController : public CommandCategoryController {
public:
    /**
     * Handle a General Command
     * @param cmd Command to handle
     * @return The result of the command. This should be sent back to the sender of the command
     */
    RobotMessage handle(const ControllerMessage &cmd, std::function<void(RobotMessage &)> callback) override;

    uint8_t getCategoryID() override;

    GeneralCommandController();

    std::pair<uint8_t, uint8_t> getParameterLimits(uint8_t command_id) override;

};
