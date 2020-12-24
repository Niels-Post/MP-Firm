#include <communication/communicationboundary/NRF24CommunicationBoundary.hpp>


NRF24CommunicationBoundary::NRF24CommunicationBoundary(NRFConfiguration &_config) : config(_config),
                                                                                    nrfRadio(config.pin_ce, config.pin_csn) {
    nrfRadio.begin();
    nrfRadio.setPALevel(config.palevel);


    if (config.enable_dynamic_payload_length) {
        nrfRadio.enableDynamicPayloads();
    } else {
        nrfRadio.disableDynamicPayloads();
        nrfRadio.setPayloadSize(config.payload_size);
    }

    nrfRadio.setAutoAck(config.enable_autoack);

    nrfRadio.setChannel(config.channel);

    nrfRadio.openReadingPipe(1, config.base_reading_pipe & ~0xFFu);
    nrfRadio.openWritingPipe(config.base_writing_pipe & ~0xFFu);

    nrfRadio.powerUp();
    nrfRadio.startListening();
}


bool NRF24CommunicationBoundary::sendMessage(const Response &message) {
    nrfRadio.stopListening();
    bool sendStatus = nrfRadio.write(&message, message.size());
    nrfRadio.startListening();
    return sendStatus;
}

bool NRF24CommunicationBoundary::isMessageAvailable() {
    return nrfRadio.available();
}

Command NRF24CommunicationBoundary::getNextMessage() {
    auto payloadSize = nrfRadio.getDynamicPayloadSize();
    uint8_t payload[payloadSize];
    nrfRadio.read(payload, payloadSize);
    Command cmd = Command::parse(payload, payloadSize);

    return cmd;
}


