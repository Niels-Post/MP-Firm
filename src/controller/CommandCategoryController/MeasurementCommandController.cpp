
#include <controller/CommandCategoryController/MeasurementCommandController.hpp>


RobotMessage MeasurementCommandController::handle(const ControllerMessage &cmd) {
    return {0, SuccessCode::BAD_PARAMETERS, nullptr};
}

uint8_t MeasurementCommandController::getCategoryID() {
    return 2;
}
