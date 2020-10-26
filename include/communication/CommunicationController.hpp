#pragma once

#include <RF24.h>
#include <communication/handler/GeneralCommandHandler.hpp>
#include <communication/handler/ActionCommandHandler.hpp>
#include <communication/handler/MeasurementCommandHandler.hpp>

#include <util/StackQueue.hpp>

#include <communication/command/Command.hpp>
#include <communication/command/ReturnCommand.hpp>

class PMSVSettings;


class ReturnCommand;

/**
 * Controller for the wireless communication aspect of the robot.
 *
 * This controller continuously checks for received RF24 Commands, parses them, and invokes a \refitem{CommandHandler} for them.
 * The controller then transmits the ReturnCode from the handler to the sender of the command
 */

class CommunicationController {
private:
    /// The radio used to communicate with the other party
    RF24                      nrfRadio;
    /// A handler for commands in the category GENERAL
    GeneralCommandHandler     generalCommandHandler;
    /// A handler for commands in the category ACTION
    ActionCommandHandler      actionCommandHandler;
    /// A handler for commands in the category MEASUREMENT
    MeasurementCommandHandler measurementCommandHandler;
    /// Queue of commands that are still to be handled
    StackQueue<Command, 20>            commandQueue;

    ///


protected:
    /**
     * Retrieve the next command from the queue, and handle it.
     */
    void handleQueuedCommand();

    /**
     * Send a ReturnCommand as a result of a Command
     * @param returnCommand The returnCommand to send
     */
    void sendReturnCommand(const ReturnCommand &returnCommand);

    /**
     * If data is available on RF24, try to parse the data as command, and add it to the commandQueue
     *
     * When no data is available, this function returns
     * When a command is inproperly formatted, the function automatically transmits the error code BAD_PARAMETERS to the sender
     */
    void parseNextCommand();

public:
    CommunicationController(const PMSVSettings &settings, MovementController &movementController);

    /**
     * Check for received messages and handle them.
     */
    void update();


};

