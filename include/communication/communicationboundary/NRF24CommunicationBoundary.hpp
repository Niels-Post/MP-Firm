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

#include <communication/communicationboundary/NRF24Configuration.hpp>

#include <core/communication/BaseCommunicationBoundary.hpp>
#include <core/PMSVSettings.hpp>


/**
 * A message boundary that sends and receives messages using the NRF24L01 module by Nordic
 *
 * For information about configuration parameters, refer to
 * https://www.sparkfun.com/datasheets/Components/SMD/nRF24L01Pluss_Preliminary_Product_Specification_v1_0.pdf
 */
class NRF24CommunicationBoundary : public BaseCommunicationBoundary {
    /// Configuration of the NRF Boundary
    NRFConfiguration &config;

    PMSVSettings &settings;

    /// The radio used to communicate with the other party
    RF24 nrfRadio;

public:
    /**
     * Constructor for the NRF boundary
     *
     * Sets up all required parameters for the NRF module using the given configuration.
     * Then powers up the module and starts listening.
     *
     * @param _config Configuration to set up
     */
    NRF24CommunicationBoundary(NRFConfiguration &_config, PMSVSettings &settings);

    /**
     * Send a message over RF to the controller
     *
     * When Auto Acknowledge is enabled, sendMessage only returns true after acknowledgement is received.
     * @param message Message to send
     * @return True if sending was successful
     */
    bool sendMessage(const Response &message) override;

    /**
     * Check if data is ready to be read from the NRF module
     * @return True if any data is available
     */
    bool isMessageAvailable() override;

    /**
     * Parse and return the first available message
     * @return The message
     */
    Command getNextMessage() override;

};