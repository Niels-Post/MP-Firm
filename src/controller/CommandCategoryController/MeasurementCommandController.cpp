
#include <controller/CommandCategoryController/MeasurementCommandController.hpp>


RobotMessage MeasurementCommandController::handle(const ControllerMessage &cmd, std::function<void(RobotMessage &)> callback) {
    return {0, SuccessCode::UNKNOWN_COMMAND};
}

uint8_t MeasurementCommandController::getCategoryID() {
    return 2;
}

std::pair<uint8_t, uint8_t> MeasurementCommandController::getParameterLimits(uint8_t command_id) {
    switch (command_id) {
        case MeasurementCommand::GET_MEASUREMENT_RAW:
        case MeasurementCommand::GET_DISTANCE_SENSOR:
            return {1, 2};
        default:
            return {255, 255};
    }
}
