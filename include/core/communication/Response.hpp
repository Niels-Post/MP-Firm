#pragma once


#include <cstdint>

/**
 * Possible return codes for a wireless command.
 *
 * ReturnCodes are packed in a \refitem{ReturnCommand} and sent back to the sender.
 */
enum class SuccessCode : uint8_t {
    /// The requested action was performed successfully
    SUCCESS        = 0,
    /// Special case: Action started is used when the robot cannot immediately send a response. The robot does not send this code
    ACTION_STARTED = 1,
    /// The robot cannot handle the command because it was busy with another action
    ROBOT_BUSY     = 2,
    /// Performing the requested action was impossible due to a hardware error
    HARDWARE_ERROR = 3,
    /// A reading was requested for a sensor that doesn't exist
    NO_SUCH_SENSOR = 4,
    /// The parameters given to the argument had the wrong length
    BAD_PARAMETERS = 5,
    /// Something went wrong parsing the command
    COMMAND_PARSE_ERROR = 6,
    /// Unknown Command Category
    UNKOWN_COMMAND_CATEGORY = 7,
    /// The command requested is unknown
    UNKNOWN_COMMAND = 8,
    /// Do not send a response for this command
    NO_RESPONSE = 9

};

/**
 * A response that is sent by the Robot to respond to a given \refitem{Command}
 */
struct Response {
    /// The message id of the original Command. This can be used to match a response to a sent command on the other side
    uint8_t     message_id;
    /// ReturnCode for the message
    SuccessCode successCode;
    /// (Optional) the data returned from the Command
    uint8_t     data[4];
    /// Size of the data returned
    uint8_t   data_size;

    /**
     * Create a Response object
     */
    Response(uint8_t messageId, SuccessCode returnCode, uint8_t data_length = 0, const uint8_t *dat = nullptr);

    /**
     * Create a Response object
     */
    Response(SuccessCode returnCode, uint8_t data_length = 0, const uint8_t *dat = nullptr);

    /**
     * Get the byte size of this command
     * @return Total size of the command in bytes
     */
    uint8_t size() const {
        return 2 + data_size;
    }
};
