#include <communication/commandcontroller/CommandController_Measurement.hpp>
#include <core/communication/CommandRegistry.hpp>


Response CommandController_Measurement::handle(const Command &cmd, ResponseCallback callback) {
    return {0, SuccessCode::UNKNOWN_COMMAND};
}

uint8_t CommandController_Measurement::getCategoryID() {
    return 2;
}

std::pair<uint8_t, uint8_t> CommandController_Measurement::getParameterLimits(uint8_t command_id) {
    switch (command_id) {
        case MeasurementCommand::GET_MEASUREMENT_RAW:
        case MeasurementCommand::GET_DISTANCE_SENSOR:
            return {1, 2};
        default:
            return {255, 255};
    }
}
