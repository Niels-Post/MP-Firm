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

#include <communication/commandcontroller/CommandController_Measurement.hpp>
#include <communication/CommandRegistry.hpp>


Response CommandController_Measurement::handle(const Command &cmd, ResponseCallback callback) {
    return {0, SuccessCode::UNKNOWN_COMMAND};
}

uint8_t CommandController_Measurement::getCategoryID() {
    return 2;
}

std::pair<uint8_t, uint8_t> CommandController_Measurement::getParameterLimits(uint8_t command_id) {
    switch (command_id) {
        case MeasurementCommand::GET_MEASUREMENT_RAW:
        case MeasurementCommand::GET_DISTANCE_SENSOR:
            return {1, 2};
        default:
            return {255, 255};
    }
}
