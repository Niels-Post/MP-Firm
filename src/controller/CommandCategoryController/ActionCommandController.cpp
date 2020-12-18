#include <controller/CommandCategoryController/ActionCommandController.hpp>

#include <controller/MovementController.hpp>
#include <Arduino.h>
RobotMessage ActionCommandController::handle(const ControllerMessage &cmd, std::function<void(RobotMessage &)> callback) {
    SuccessCode code = SuccessCode::BAD_PARAMETERS;
    switch (cmd.command_id) {
        case CANCEL_MOVEMENT:
            code = movementController.halt();
            break;
        case START_MOVE_MM: {
            if (cmd.parameter_length > 2) {
                movementController.setDirection(cmd.parameters[2]);
            }

            code = movementController.startMoveMM(cmd.get_param16(0), callback);
            break;
        }
        case START_ROTATE_DEGREES:
            code = movementController.startRotateDegrees(cmd.get_param16(0), cmd.parameters[2],
                                                         callback);

            break;
        case SET_SPEED:
            code = movementController.setSpeed(cmd.parameters[0]);
            break;
        default:
            code = SuccessCode::BAD_PARAMETERS;
    }

    return {cmd.message_id, code};
}

ActionCommandController::ActionCommandController(MovementController &movementController) : movementController(
        movementController) {}

uint8_t ActionCommandController::getCategoryID() {
    return 1;
}

std::pair<uint8_t, uint8_t> ActionCommandController::getParameterLimits(uint8_t command_id) {
    switch (command_id) {
        case CANCEL_MOVEMENT:
            return {0, 0};
        case START_MOVE_MM:
            return {2, 3};
        case START_ROTATE_DEGREES:
            return {3, 3};;
        case SET_SPEED:
            return {1, 1};
        default:
            return {255, 255};
    }
}
