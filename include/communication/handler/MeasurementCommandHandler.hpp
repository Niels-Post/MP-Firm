#pragma once
#include <communication/handler/CommandHandler.hpp>

class MeasurementCommandHandler: public CommandHandler {
public:
    ReturnCommand handle(const Command &cmd) override;
};

