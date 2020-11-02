#pragma once

#include <arduino.h>
#include <boundary/communication/MessageBoundary.hpp>
class UartMessageBoundary: public MessageBoundary {
    UARTClass &interface;

public:
    UartMessageBoundary(UARTClass &anInterface);

    bool sendMessage(const RobotMessage &command) override;

    bool isMessageAvailable() override;

    ControllerMessage getNextMessage() override;
};