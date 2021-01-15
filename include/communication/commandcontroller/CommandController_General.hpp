/*
 * Copyright (c) 2021. Niels Post. AI Lab Vrije Universiteit Brussel.
 *
 * This file is part of MP-Firm.
 *
 * MP-Firm is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * MP-Firm is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with MP-Firm.  If not, see <https://www.gnu.org/licenses/>.
 */

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

    /**
     * \copydoc BaseCommandController::getCategoryID()
     */
    uint8_t getCategoryID() override;

    CommandController_General(PMSVSettings &settings, ConfigurationValue<uint8_t> &robotIdConfig);

    /**
     * \copydoc BaseCommandController::getParameterLimits(uint8_t)
     */
    std::pair<uint8_t, uint8_t> getParameterLimits(uint8_t command_id) override;

};
