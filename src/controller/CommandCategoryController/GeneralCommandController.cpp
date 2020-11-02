#include <controller/CommandCategoryController/GeneralCommandController.hpp>



RobotMessage GeneralCommandController::handle(const ControllerMessage &cmd) {
    return {0, SuccessCode::UNKNOWN_COMMAND};
}

uint8_t GeneralCommandController::getCategoryID() {
    return 0;
}

GeneralCommandController::GeneralCommandController() {}

std::pair<uint8_t, uint8_t> GeneralCommandController::getParameterLimits(uint8_t command_id) {
    switch (command_id) {
        case GeneralCommand::SET_COMMUNICATION_ACTIVEMODE:
            return {1, 1};
        default:
            return {255, 255};
    }
}
