//
// Created by niels on 30/10/2020.
//

#include "boundary/communication/commandboundary/NRFBoundary.hpp"

NRFBoundary::NRFBoundary(uint16_t pin_ce, uint16_t pin_csn, uint8_t channel, uint64_t readingPipe, uint64_t writingPipe,
                         bool enableAutoAck,
                         bool enableDynamicPayloads, uint8_t staticPayloadLength, rf24_pa_dbm_e paLevel)
        : nrfRadio(pin_ce, pin_csn) {
    // Power up and set output power
    nrfRadio.begin();
    nrfRadio.setPALevel(paLevel);


    if (enableDynamicPayloads) {
        nrfRadio.enableDynamicPayloads();
    } else {
        nrfRadio.disableDynamicPayloads();
        nrfRadio.setPayloadSize(staticPayloadLength);
    }

    nrfRadio.setAutoAck(enableAutoAck);

    nrfRadio.setChannel(channel);

    nrfRadio.openReadingPipe(1, readingPipe);

    nrfRadio.openWritingPipe(writingPipe);

    nrfRadio.powerUp();

    nrfRadio.printDetails();
}



bool NRFBoundary::sendMessage(const RobotMessage &robotMessage) {
    nrfRadio.stopListening();
    bool status = nrfRadio.write(&robotMessage, robotMessage.size());
    nrfRadio.startListening();
    return status;
}

bool NRFBoundary::isMessageAvailable() {
    return nrfRadio.available();
}

ControllerMessage NRFBoundary::getNextMessage()  {
    auto    size = nrfRadio.getDynamicPayloadSize();
    uint8_t data[size];
    nrfRadio.read(data, size);
    ControllerMessage cmd;

    if (ControllerMessage::validate(data, size)) {
        cmd = ControllerMessage::parse(data, size);
    }

    return cmd;
}



