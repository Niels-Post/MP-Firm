#pragma once

#include <communication/handler/CommandHandler.hpp>

class MovementController;

class ActionCommandHandler: public CommandHandler {
    MovementController &movementController;
public:
    ReturnCommand handle(const Command &cmd) override;

    ActionCommandHandler(MovementController &movementController);
};
