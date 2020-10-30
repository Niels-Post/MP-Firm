#pragma once

#include <entity/RobotMessage.hpp>
#include <entity/ControllerMessage.hpp>

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
     * This method is called when a command is received with a category_id equal to getCategoryID().
     * @param cmd Command to handle
     * @return The result of the command. This should be sent back to the sender of the command
     */
    virtual RobotMessage handle(const ControllerMessage &cmd) = 0;
};
