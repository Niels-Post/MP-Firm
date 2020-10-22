#pragma once

#include <cstdint>
#include <cstdio>

/**
 * Possible return codes for a wireless command.
 *
 * ReturnCodes are packed in a \refitem{ReturnCommand} and sent back to the sender.
 */
enum class ReturnCode : uint8_t {
    /// The requested action was performed successfully
    SUCCESS        = 0,
    /// The robot cannot handle the command because it was busy with another action
    ROBOT_BUSY     = 1,
    /// Performing the requested action was impossible due to a hardware error
    HARDWARE_ERROR = 2,
    /// (Only for movement) Performing the requested action failed because a motor was stalling
    MOTOR_STALL    = 3,
    /// The command received by the robot was ill-formatted
    BAD_PARAMETERS = 4,
    /// A reading was requested for a sensor that doesn't exist
    NO_SUCH_SENSOR = 5
};

/**
 * A command that is sent by the Robot to respond to a given \refitem{Command}
 */
struct ReturnCommand {
    /// The message id of the original Command. This can be used to match a returncommand to a sent command on the other side
    uint8_t    message_id;
    /// ReturnCode for the message
    ReturnCode returnCode;
    /// (Optional) the data returned from the Command
    uint8_t    data[4];
    /// Size of the data returned
    size_t     data_size;

    /**
     * Create a ReturnCommand
     */
    ReturnCommand(uint8_t messageId, ReturnCode returnCode, const uint8_t *dat);
};
