#pragma once

#include <boundary/communication/CommandBoundary.hpp>
#include <RF24.h>


class NRFBoundary: public CommandBoundary {
    /// The radio used to communicate with the other party
    RF24                      nrfRadio;


public:
    NRFBoundary(uint16_t pin_ce, uint16_t pin_csn, uint8_t channel,  uint64_t readingPipe, uint64_t writingPipe,
                bool enableAutoAck = true, bool enableDynamicPayloads = true, uint8_t staticPayloadLength = 0,
                rf24_pa_dbm_e paLevel = RF24_PA_MIN);

    bool sendMessage(const RobotMessage &command) override;

    bool isMessageAvailable() override;

    ControllerMessage getNextMessage() override;

};