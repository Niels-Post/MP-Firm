#include <communication/commandcontroller/CommandController_General.hpp>
#include <communication/CommandRegistry.hpp>


Response CommandController_General::handle(const Command &cmd, ResponseCallback callback) {
    auto cmd_id = static_cast<GeneralCommand>(cmd.command_id);
    switch(cmd_id) {
        case REBOOT:
            rstc_start_software_reset(RSTC);
            break;
        case SET_ID:
            if(pmsvSettings.robot_id != 0) {
                return {cmd.message_id, SuccessCode::NO_RESPONSE};
            }
            pmsvSettings.robot_id = cmd.parameters[0];
            configRobotId.store();
            Response res{cmd.message_id, SuccessCode::SUCCESS};
            callback(res);
            rstc_start_software_reset(RSTC);
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
            return {0, 0};
        case SET_ID:
            return {1, 1};
        default:
            return {255, 255};

    }
}
