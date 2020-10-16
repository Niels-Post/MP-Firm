#include <queue>

#include <communication/CommunicationController.hpp>
#include <movement/MovementController.hpp>
#include <pmsv/PMSVSettings.hpp>

#include <communication/command/ReturnCommand.hpp>
#include <communication/command/Command.hpp>


CommunicationController::CommunicationController(const PMSVSettings &settings, MovementController &movementController)
        : nrfRadio(settings.nrf_pin_ce,
                   settings.nrf_pin_csn), generalCommandHandler(), actionCommandHandler(movementController), measurementCommandHandler(){
    nrfRadio.begin();
    nrfRadio.setPALevel(settings.nrf_palevel);

    if (settings.nrf_enable_dynamicpayloads) {
        nrfRadio.enableDynamicPayloads();
    } else {
        nrfRadio.disableDynamicPayloads();
        nrfRadio.setPayloadSize(settings.nrf_payload_size);
    }

    nrfRadio.setAutoAck(settings.nrf_enable_autoack);

    nrfRadio.setChannel(settings.nrf_channel);

    nrfRadio.openReadingPipe(1, settings.nrf_readingpipe);

    nrfRadio.openWritingPipe(settings.nrf_writingpipe);

    nrfRadio.powerUp();

    nrfRadio.printDetails();
    delay(2000);
}

void CommunicationController::update() {
    nrfRadio.startListening();
    if (nrfRadio.available()) {
        parseNextCommand();
    }

    if (!commandQueue.empty()) {
        handleCommand(commandQueue.front());
        commandQueue.pop();
    }

}

void CommunicationController::parseNextCommand() {
    auto size = nrfRadio.getDynamicPayloadSize();
    uint8_t data[size];
    nrfRadio.read(data, size);

    if (Command::validate(data, size)) {
        commandQueue.push(Command::parse(data, size));
        nrfRadio.stopListening();
    } else {
        Serial.println("Invalid command received");
    }
}

void CommunicationController::handleCommand(const Command &command) {
    switch (static_cast<CommandCategory>(command.category_id)) {
        case CommandCategory::GENERAL:
            sendReturnCommand(generalCommandHandler.handle(command));
            break;
        case CommandCategory::ACTION:
            sendReturnCommand(actionCommandHandler.handle(command));
            break;
        case CommandCategory::MOVEMENT:
            sendReturnCommand(measurementCommandHandler.handle(command));
            break;
    }
}

void CommunicationController::sendReturnCommand(const ReturnCommand &command) {
    nrfRadio.stopListening();
    if(!nrfRadio.write(&command, 6) )
    {
        Serial.println("Sending return failed");
    }
}
