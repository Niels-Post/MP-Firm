#pragma once

#include <communication/command/Command.hpp>
#include <communication/command/ReturnCommand.hpp>

class CommandHandler {
public:
    virtual ReturnCommand handle(const Command &cmd) = 0;
};
