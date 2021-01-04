#pragma once


#include <core/communication/BaseCommandController.hpp>
#include <core/PMSVSettings.hpp>
#include <core/configuration/ConfigurationValue.hpp>

/**
 * Handles commands in the category \refitem{CommandCategory::GENERAL}
 */
class CommandController_General : public BaseCommandController {
    PMSVSettings &pmsvSettings;
    ConfigurationValue<uint8_t> &configRobotId;
public:
    /**
     * Handle a General Command
     * @param cmd Command to handle
     * @return The result of the command. This should be sent back to the sender of the command
     */
    Response handle(const Command &cmd, ResponseCallback callback) override;

    uint8_t getCategoryID() override;

    CommandController_General(PMSVSettings &settings, ConfigurationValue<uint8_t> &robotIdConfig);

    std::pair<uint8_t, uint8_t> getParameterLimits(uint8_t command_id) override;

};
