#include <controller/CommandCategoryController/GeneralCommandController.hpp>



RobotMessage GeneralCommandController::handle(const ControllerMessage &cmd) {
    return {0, SuccessCode::BAD_PARAMETERS, nullptr};
}

uint8_t GeneralCommandController::getCategoryID() {
    return 0;
}

GeneralCommandController::GeneralCommandController() {}
