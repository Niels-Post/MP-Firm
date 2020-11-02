//
// Created by niels on 02/11/2020.
//

#include <boundary/communication/messageboundary/UartMessageBoundary.hpp>

bool UartMessageBoundary::sendMessage(const RobotMessage &command) {
    auto size_written = interface.write((const uint8_t *) (&command), command.size());
    return size_written == command.size();
}

bool UartMessageBoundary::isMessageAvailable() {
    return interface.available() >= 3;
}

ControllerMessage UartMessageBoundary::getNextMessage() {
    uint8_t data[ControllerMessage::maxMessageSize() + 1];

    // Read the next command
    // Note that in this boundary, we use a ~ to indicate the end of a command, since UART itself does not indicate ends of messages
    // We add one to the maximum message size, since the ~ also needs to be read
    size_t length = interface.readBytesUntil('~', data, ControllerMessage::maxMessageSize() + 1);

    // Parse the data. Should the data be ill-formatted, parse will automatically return an INVALID command.
    return ControllerMessage::parse(data, length);
}

UartMessageBoundary::UartMessageBoundary(UARTClass &anInterface) : interface(anInterface) {}
