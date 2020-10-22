#pragma once

#include <communication/handler/CommandHandler.hpp>

/**
 * Handles commands in the category \refitem{CommandCategory::MEASUREMENT}
 */
class MeasurementCommandHandler : public CommandHandler {
public:
    /**
     * Handle a Measurement Command
     * @param cmd Command to handle
     * @return The result of the command, usually containing a measurement. This should be sent back to the sender of the command
     */
    ReturnCommand handle(const Command &cmd) override;
};

