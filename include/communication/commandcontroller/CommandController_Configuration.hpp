#pragma once

#include <core/communication/BaseCommandController.hpp>

#include <core/configuration/ConfigurationValue.hpp>
#include <core/communication/Response.hpp>
#include <core/communication/Command.hpp>

#include <cstdint>
#include <utility>

/**
 * Handles commands in the category \refitem{CommandCategory::CONFIGURATION}
 */
class CommandController_Configuration : public BaseCommandController {
    std::reference_wrapper<BaseConfigurationValue> *configurationValues;
    size_t configuration_value_count ;

public:



    /**
     * Handle a Configuration Command
     * @param cmd Command to handle
     * @return The result of the command. This should be sent back to the sender of the command
     */
    Response handle(const Command &cmd, ResponseCallback callback) override;

    uint8_t getCategoryID() override;

	CommandController_Configuration(std::reference_wrapper<BaseConfigurationValue> *configurationValues,
                                    size_t configurationValueCount);

	std::pair<uint8_t, uint8_t> getParameterLimits(uint8_t command_id) override;

};

