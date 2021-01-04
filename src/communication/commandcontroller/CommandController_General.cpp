#include <communication/commandcontroller/CommandController_General.hpp>
#include <communication/CommandRegistry.hpp>


Response CommandController_General::handle(const Command &cmd, ResponseCallback callback) {
    auto cmd_id = static_cast<GeneralCommand>(cmd.command_id);
    switch(cmd_id) {
        case REBOOT:
            rstc_start_software_reset(RSTC);
            break;
        case DISCOVER:
            if(pmsvSettings.robot_id == 0) {
                return {cmd.message_id, SuccessCode::SUCCESS};
            }
            return {cmd.message_id, SuccessCode::NO_RESPONSE};
        case RESET_ID:
            pmsvSettings.robot_id = 0;
            configRobotId.store();
            rstc_start_software_reset(RSTC);
            break;
    }
    return {cmd.message_id, SuccessCode::UNKNOWN_COMMAND};
}

uint8_t CommandController_General::getCategoryID() {
    return 0;
}

CommandController_General::CommandController_General(PMSVSettings &settings, ConfigurationValue<uint8_t> &robotIdConfig)
        : pmsvSettings{settings}, configRobotId{robotIdConfig} {}

std::pair<uint8_t, uint8_t> CommandController_General::getParameterLimits(uint8_t command_id) {
    auto cmd_id = static_cast<GeneralCommand>(command_id);

    switch (cmd_id) {
        case REBOOT:
        case DISCOVER:
        case RESET_ID:
            return {0, 0};
        default:
            return {255, 255};

    }
}
