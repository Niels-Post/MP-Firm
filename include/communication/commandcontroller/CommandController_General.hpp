#pragma once


#include <core/communication/BaseCommandController.hpp>

/**
 * Handles commands in the category \refitem{CommandCategory::GENERAL}
 */
class CommandController_General : public BaseCommandController {
public:
    /**
     * Handle a General Command
     * @param cmd Command to handle
     * @return The result of the command. This should be sent back to the sender of the command
     */
    Response handle(const Command &cmd, ResponseCallback callback) override;

    uint8_t getCategoryID() override;

    CommandController_General();

    std::pair<uint8_t, uint8_t> getParameterLimits(uint8_t command_id) override;

};
