#pragma once

#include <controller/CommandCategoryController.hpp>

/**
 * Handles commands in the category \refitem{CommandCategory::MEASUREMENT}
 */
class MeasurementCommandController : public CommandCategoryController {
public:
    /**
     * Handle a Measurement Command
     * @param cmd Command to handle
     * @return The result of the command, usually containing a measurement. This should be sent back to the sender of the command
     */
    RobotMessage handle(const ControllerMessage &cmd) override;

    uint8_t getCategoryID() override;
};

