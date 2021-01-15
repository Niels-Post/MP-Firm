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

#include <communication/communicationboundary/NRF24CommunicationBoundary.hpp>


NRF24CommunicationBoundary::NRF24CommunicationBoundary(NRFConfiguration &_config, PMSVSettings &settings)
        : config(_config),
          settings(settings), nrfRadio(config.pin_ce, config.pin_csn) {
    nrfRadio.begin();


    for (int i = 0; i < 5; i++) {
        nrfRadio.closeReadingPipe(i);
    }

    nrfRadio.setPALevel(config.palevel);
    nrfRadio.setDataRate(RF24_250KBPS);


    if (config.enable_dynamic_payload_length) {
        nrfRadio.enableDynamicPayloads();
    } else {
        nrfRadio.disableDynamicPayloads();
        nrfRadio.setPayloadSize(config.payload_size);
    }

    nrfRadio.setRetries(15, 15);

    nrfRadio.setChannel(config.channel);

    const uint64_t base_address_mask = 0x000000FFu;

    if (settings.robot_id != 0) {
        nrfRadio.openReadingPipe(0, config.base_reading_pipe);
        nrfRadio.openReadingPipe(1, (config.base_reading_pipe & ~base_address_mask) | settings.robot_id);
        nrfRadio.setAutoAck(true);
        nrfRadio.setAutoAck(0, false);
    } else {
        nrfRadio.openReadingPipe(0, config.base_reading_pipe);
        nrfRadio.setAutoAck(false);
    }
    nrfRadio.powerUp();
    nrfRadio.startListening();

    nrfRadio.printDetails();
}


bool NRF24CommunicationBoundary::sendMessage(const Response &message) {
    nrfRadio.stopListening();
    const uint64_t base_address_mask = 0x000000FFu;
    if(message.broadcast) {
        nrfRadio.openWritingPipe(config.base_writing_pipe);
    } else {
        nrfRadio.openWritingPipe((config.base_reading_pipe & ~base_address_mask) | settings.robot_id);
        nrfRadio.setAutoAck(0, true);
    }

    uint8_t data[message.size()];
    message.write_bytes(data);

    bool sendStatus = nrfRadio.write(data, message.size());

    if(!message.broadcast) {
        nrfRadio.setAutoAck(0, false);
    }

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


