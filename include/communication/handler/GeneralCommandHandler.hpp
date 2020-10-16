#pragma once
#include <communication/handler/CommandHandler.hpp>

class GeneralCommandHandler: public CommandHandler {
public:
    ReturnCommand handle(const Command &cmd) override;

};
