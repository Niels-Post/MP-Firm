#include <controller/CommandCategoryController/ActionCommandController.hpp>

#include <controller/MovementController.hpp>


RobotMessage ActionCommandController::handle(const ControllerMessage &cmd) {
    SuccessCode code = SuccessCode::BAD_PARAMETERS;
    switch (static_cast<ActionCommand>(cmd.command_id)) {
        case ActionCommand::CANCEL_MOVEMENT:
            code = movementController.halt();
            break;
        case ActionCommand::START_MOVE_MM: {
            if (cmd.parameter_length > 2) {
                movementController.setDirection(cmd.parameters[2]);
            }

            code = movementController.startMoveMM(cmd.get_param16(0));
            break;
        }
        case ActionCommand::START_ROTATE_DEGREES:
            code = movementController.startRotateDegrees(cmd.get_param16(0), cmd.parameters[2]);

            break;
        case ActionCommand::SET_SPEED:
            code = movementController.setSpeed(cmd.parameters[0]);
            break;
    }

    return {cmd.message_id, code};
}

ActionCommandController::ActionCommandController(MovementController &movementController) : movementController(
        movementController) {}

uint8_t ActionCommandController::getCategoryID() {
    return 1;
}
