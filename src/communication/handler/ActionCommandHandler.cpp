//
// Created by Niels on 16/10/2020.
//

#include <communication/handler/ActionCommandHandler.hpp>

#include <movement/MovementController.hpp>
#include <communication/command/ReturnCommand.hpp>
#include <communication/command/Command.hpp>

ReturnCommand ActionCommandHandler::handle(const Command &cmd) {
    switch(static_cast<ActionCommand>(cmd.command_id)){
        case ActionCommand::CANCEL_MOVEMENT:
            movementController.halt();
            break;
        case ActionCommand::START_MOVE_STEPS: {
            if(cmd.parameter_length > 2) {
                movementController.setDirection(cmd.parameters[2]);
            }

            movementController.startMoveSteps(cmd.get_param16(0));
            break;
        }
        case ActionCommand::START_MOVE_CM: {
            if(cmd.parameter_length > 2) {
                movementController.setDirection(cmd.parameters[2]);
            }

            movementController.startMoveSteps(cmd.get_param16(0));
            break;
        }
        case ActionCommand::START_ROTATE_DEGREES:
            movementController.startRotateDegrees(cmd.get_param16(0), cmd.parameters[2]);

            break;
        case ActionCommand::SET_SPEED:
            movementController.setSpeed(cmd.parameters[0]);
            break;
    }

    return {0, ReturnCode::SUCCESS, nullptr};
}

ActionCommandHandler::ActionCommandHandler(MovementController &movementController) : movementController(
        movementController) {}
