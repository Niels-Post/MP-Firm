#include <communication/communicationboundary/NRF24CommunicationBoundary.hpp>


NRF24CommunicationBoundary::NRF24CommunicationBoundary(NRFConfiguration &_config, PMSVSettings &settings)
        : config(_config),
          settings(settings), nrfRadio(config.pin_ce, config.pin_csn) {
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

    const uint64_t base_address_mask = 0x000000FFu;

    nrfRadio.openReadingPipe(1, config.base_reading_pipe & ~base_address_mask);
    nrfRadio.openReadingPipe(2, (config.base_reading_pipe & ~base_address_mask) | settings.robot_id);
    nrfRadio.openWritingPipe((config.base_writing_pipe & ~base_address_mask) | settings.robot_id);

    nrfRadio.powerUp();

    nrfRadio.printDetails();
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


