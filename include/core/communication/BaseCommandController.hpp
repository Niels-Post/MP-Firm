#pragma once

#include <core/communication/Response.hpp>
#include <core/communication/Command.hpp>

#include <functional>
#include <cstdint>

typedef std::function<void(Response &)> ResponseCallback;

/**
  * Interface to handle commands in a specific category
 */
class BaseCommandController {
public:
    /**
     * Get the category ID of commands that this commandhandler handles
     * @return The category ID for this Controller
     */
    virtual uint8_t getCategoryID() = 0;

    /**
     * Process and execute a command in a message, and return a success code
     * @param cmd Message to handle
     * @param callback Delayed result callback
     *
     * When the command response can be immediately returned, handle should do so.
     * If this is not possible, the handle should return a Response with the success code ACTION_STARTED,
     * and later, when the action is done pass the final result onto the given MessageCallback.
     * @return The result of the command. This should be sent back to the sender of the command
     */
    virtual Response handle(const Command &cmd, ResponseCallback callback ) = 0;

    /**
     * Get the minimum and maximum parameter size of each command in this category.
     *
     * When a command id is unkown, this method should return a pair containing {255,255}
     * @param command_id The command id the bounds are requested for
     * @return A pair of the minimum and maximum size
     */
    virtual std::pair<uint8_t, uint8_t> getParameterLimits(uint8_t command_id) = 0;
};
