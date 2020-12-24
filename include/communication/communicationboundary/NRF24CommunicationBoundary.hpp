#pragma once

#include <communication/communicationboundary/NRF24Configuration.hpp>

#include <core/communication/BaseCommunicationBoundary.hpp>




/**
 * A message boundary that sends and receives messages using the NRF24L01 module by Nordic
 *
 * For information about configuration parameters, refer to
 * https://www.sparkfun.com/datasheets/Components/SMD/nRF24L01Pluss_Preliminary_Product_Specification_v1_0.pdf
 */
class NRF24CommunicationBoundary : public BaseCommunicationBoundary {
    /// Configuration of the NRF Boundary
    NRFConfiguration &config;

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
    NRF24CommunicationBoundary(NRFConfiguration &_config);

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