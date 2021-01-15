#pragma once


#include <core/communication/BaseCommunicationBoundary.hpp>
#include <core/communication/BaseCommandController.hpp>

#include <core/communication/Command.hpp>
#include <core/util/StackQueue.hpp>

#include <utility>
#include <cstddef>


/**
 * Controller for the wireless communication aspect of the robot.
 *
 * This controller continuously checks for received RF24 Commands, parses them, and invokes a \refitem{CommandHandler} for them.
 * The controller then transmits the ReturnCode from the handler to the sender of the command
 */
class CommunicationController {
private:
    /// The max amount of commands the robot queues before they new commands are dropped
    static size_t const MAX_QUEUE_LENGTH = 20;
    /// CommunicationBoundary to send and receive commands through
    BaseCommunicationBoundary &communicationBoundary;
    /// Queue of commands that are still to be handled
    StackQueue<Command, MAX_QUEUE_LENGTH> commandQueue;
    /// All CommandControllers
    std::reference_wrapper<BaseCommandController> *commandControllers;
    /// Size of the commandcontroller
    size_t commandControllerCount;

protected:
    /**
     * Find the command controller that handles a specific command
     *
     * Returns a nullpointer if none was found
     * @param cmd Command to find a controller for
     * @return A pointer to the command controller
     */
    BaseCommandController * getCommandController(const Command &cmd);


    /**
     * Retrieve the next command from the queue, and handle it.
     */
    void handleQueuedCommand();



    /**
     * If data is available on the communicationboundary, parse a message and queue it for handling.
     *
     * When no data is available, this function returns
     * When a command is inproperly formatted, the function automatically transmits the error code BAD_PARAMETERS to the sender
     */
    void queueReceivedCommands();



public:
    CommunicationController(BaseCommunicationBoundary &communicationBoundary,
                            std::reference_wrapper<BaseCommandController> *commandControllers,
                            size_t commandControllerCount)
            : communicationBoundary(communicationBoundary), commandQueue(), commandControllers{commandControllers},
              commandControllerCount{commandControllerCount} {

    }


    /**
     * Check for received messages and handle them.
     */
    void update();


};

