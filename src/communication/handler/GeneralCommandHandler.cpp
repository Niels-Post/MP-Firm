//
// Created by Niels on 16/10/2020.
//

#include <communication/handler/GeneralCommandHandler.hpp>

#include <communication/command/ReturnCommand.hpp>
#include <communication/command/Command.hpp>

ReturnCommand GeneralCommandHandler::handle(const Command &cmd) {
    return {0,ReturnCode::BAD_PARAMETERS, nullptr};
}
