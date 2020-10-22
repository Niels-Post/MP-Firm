//
// Created by Niels on 16/10/2020.
//



#include <communication/command/ReturnCommand.hpp>


ReturnCommand::ReturnCommand(uint8_t messageId, ReturnCode returnCode, const uint8_t *dat) : message_id(messageId),
                                                                                             returnCode(returnCode) {
    for (size_t i = 0; i < 4; i++) {
        data[i] = dat[i];
    }
}
