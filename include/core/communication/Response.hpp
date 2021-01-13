#pragma once
#undef min
#undef max
#include <cstdint>
#include <cstddef>
#include <memory>

/**
 * Possible return codes for a wireless command.
 *
 * ReturnCodes are packed in a \refitem{ReturnCommand} and sent back to the sender.
 */
enum class SuccessCode : uint8_t {
    /// The requested action was performed successfully
    SUCCESS = 0,
    /// Special case: Action started is used when the robot cannot immediately send a response. The robot does not send this code
    ACTION_STARTED = 1,
    /// The robot cannot handle the command because it was busy with another action
    ROBOT_BUSY = 2,
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
    NO_RESPONSE = 9,
    /// Sent when a robot is already registered to a robot id
    ID_ALREADY_SET = 10

};

/**
 * A response that is sent by the Robot to respond to a given \refitem{Command}
 */
struct Response {
public:
    /// The message id of the original Command. This can be used to match a response to a sent command on the other side
    uint8_t message_id;
    /// ReturnCode for the message
    SuccessCode successCode;
    /// Should the message be broadcast or unicast?
    bool broadcast = false;

private:


    /// (Optional) the data returned from the Command
    std::shared_ptr<uint8_t []> data;
    /// Size of the data returned
    uint8_t data_size;
public:

    /**
     * Create a Response object
     */
    Response(uint8_t messageId, SuccessCode returnCode, uint8_t data_length = 0, const uint8_t *dat = nullptr,
                 bool _broadcast = false) : message_id(messageId),
                                            successCode(returnCode),broadcast(_broadcast), data{data_length > 0 ? new uint8_t[data_length] : nullptr}, data_size(data_length) {
        for (size_t i = 0; i < data_length; i++) {
            data[i] = dat[i];
        }
    }

    /**
     * Create a Response object
     */
    Response(SuccessCode returnCode, uint8_t data_length = 0, const uint8_t *dat = nullptr,
                 bool _broadcast = false): Response(0, returnCode, data_length, dat, _broadcast) {

    }

    /**
     * Get the byte size of this command
     * @return Total size of the command in bytes
     */
    uint8_t size() const {
        return 2 + data_size;
    }

    /**
     * Write the message to a byte array.
     *
     * When calling this method, make sure the byte array is at least as big as the return value of size()
     * @param write_to
     */
    void write_bytes(uint8_t *write_to) const{
        write_to[0] = message_id;
        write_to[1] = static_cast<uint8_t>(successCode);
        for(size_t i = 0; i < data_size; i++) {
            write_to[i + 2] = data[i];
        }
    }
};


