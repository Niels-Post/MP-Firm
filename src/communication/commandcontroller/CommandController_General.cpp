#include <communication/commandcontroller/CommandController_General.hpp>
#include <core/communication/CommandRegistry.hpp>


Response CommandController_General::handle(const Command &cmd, ResponseCallback callback) {
    switch(cmd.command_id) {
        case REBOOT:
            rstc_start_software_reset(RSTC);
    }
    return {0, SuccessCode::UNKNOWN_COMMAND};
}

uint8_t CommandController_General::getCategoryID() {
    return 0;
}

CommandController_General::CommandController_General() {}

std::pair<uint8_t, uint8_t> CommandController_General::getParameterLimits(uint8_t command_id) {
    switch (command_id) {
        case REBOOT:
            return {0, 0};
        default:
            return {255, 255};
    }
}
