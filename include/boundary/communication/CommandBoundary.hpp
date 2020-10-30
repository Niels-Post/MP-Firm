#pragma once


#include <entity/RobotMessage.hpp>
#include <entity/ControllerMessage.hpp>

/**
 * The commandboundary is a boundary used for transmitting and receiving commands.
 * The CommandBoundary can be extended and implemented for use with various communication methods, wireless or wired.
 *
 * It is assumed that communication is two way between 1 controller and 1 robot (it is not a busline)
 */
class CommandBoundary {
public:
    /**
     * Transmit a returncommand to the Controller
     * @param command The command to send
     */
    virtual bool sendMessage(const RobotMessage &command) = 0;

    /**
     * Should check if a command from the controller was received or is available
     */
    virtual bool isMessageAvailable() = 0;

    /**
     * Parse and return the next received command
     *
     * This method should use Command::validate to make sure a command is valid, and then use Command::parse to parse the data.
     */
    virtual ControllerMessage getNextMessage() = 0;

};