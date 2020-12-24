#pragma once


#include <core/communication/BaseCommandController.hpp>

/**
 * Handles commands in the category \refitem{CommandCategory::MEASUREMENT}
 */
class CommandController_Measurement : public BaseCommandController {
public:
    /**
     * Handle a Measurement Command
     * @param cmd Command to handle
     * @return The result of the command, usually containing a measurement. This should be sent back to the sender of the command
     */
    Response handle(const Command &cmd, ResponseCallback callback) override;

    uint8_t getCategoryID() override;

    std::pair<uint8_t, uint8_t> getParameterLimits(uint8_t command_id) override;
};

