//
// Created by Niels on 16/10/2020.
//



#include <entity/RobotMessage.hpp>


RobotMessage::RobotMessage(uint8_t messageId, SuccessCode returnCode, uint8_t data_length, const uint8_t *dat)
        : message_id(messageId),
          successCode(returnCode) {
    for (size_t i = 0; i < 4; i++) {
        data[i] = dat[i];
    }
}
