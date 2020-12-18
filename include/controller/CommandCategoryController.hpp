#pragma once

#include <entity/RobotMessage.hpp>
#include <entity/ControllerMessage.hpp>
#include <functional>

/**
  * Interface to handle commands in a specific category
 */
class CommandCategoryController {
public:
    /**
     * Get the category ID of commands that this CommandCategoryController handles
     * @return The category ID for this Controller
     */
    virtual uint8_t getCategoryID() = 0;

    /**
     * Process and execute a command in a message, and return a success code
     * @param cmd Message to handle
     * @return The result of the command. This should be sent back to the sender of the command
     */
    virtual RobotMessage handle(const ControllerMessage &cmd, std::function<void(RobotMessage &)> callback ) = 0;

    /**
     * Get the minimum and maximum size of each command in this category
     * @param command_id The command id the bounds are requested for
     * @return A pair of the minimum and maximum size
     */
    virtual std::pair<uint8_t, uint8_t> getParameterLimits(uint8_t command_id) = 0;
};
