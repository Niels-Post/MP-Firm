#pragma once

#include <RF24.h>
#include <communication/handler/GeneralCommandHandler.hpp>
#include <communication/handler/ActionCommandHandler.hpp>
#include <communication/handler/MeasurementCommandHandler.hpp>
#include <queue>

class PMSVSettings;
class Command;
class ReturnCommand;

class CommunicationController {
private:
    RF24                      nrfRadio;
    GeneralCommandHandler     generalCommandHandler;
    ActionCommandHandler      actionCommandHandler;
    MeasurementCommandHandler measurementCommandHandler;

    std::queue<Command> commandQueue;


protected:
    void handleCommand(const Command &command);
    void sendReturnCommand(const ReturnCommand &command);
    void parseNextCommand();
public:
    CommunicationController(const PMSVSettings &settings, MovementController &movementController);

    void update();


};

