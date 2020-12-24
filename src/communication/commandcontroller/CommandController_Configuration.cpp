#include <communication/commandcontroller/CommandController_Configuration.hpp>
#include <core/communication/CommandRegistry.hpp>


Response
CommandController_Configuration::handle(const Command &cmd, ResponseCallback callback) {
	Response returnMessage{cmd.message_id, SuccessCode::SUCCESS};
	switch (cmd.command_id) {
		case SET_VALUE: {
			auto id = cmd.parameters[0];
			for (size_t i = 0; i < configuration_value_count; i++) {
				if (configurationValues[i].get().getId() == id) {
					configurationValues[i].get().set((void *) (&cmd.parameters[1]));
				}
			}
			break;
		}
		case GET_VALUE: {
			auto id = cmd.parameters[0];
			returnMessage.successCode = SuccessCode::BAD_PARAMETERS;
			for (size_t i = 0; i < configuration_value_count; i++) {
				if (configurationValues[i].get().getId() == id) {
					auto data = configurationValues[i].get().get();
					returnMessage.data_size = data.second;
					for (size_t j = 0; j < data.second; j++) {
						returnMessage.data[j] = ((uint8_t *) data.first)[j];
					}
					returnMessage.successCode = SuccessCode::SUCCESS;
					break;
				}
			}

			break;
		}
		case GET_TYPE: {
			auto id = cmd.parameters[0];
			returnMessage.successCode = SuccessCode::BAD_PARAMETERS;
			for (size_t i = 0; i < configuration_value_count; i++) {
				if (configurationValues[i].get().getId() == id) {
					returnMessage.data[0] = configurationValues[i].get().getType();
					returnMessage.data_size = 1;
					returnMessage.successCode = SuccessCode::SUCCESS;
					break;
				}
			}
			break;
		}
		case LOAD:
			for (size_t i = 0; i < configuration_value_count; i++) {
				configurationValues[i].get().load();
			}
			break;
		case STORE:
			for (size_t i = 0; i < configuration_value_count; i++) {
				configurationValues[i].get().store();
			}
			break;
		case PRINT_ALL:
			for (size_t i = 0; i < configuration_value_count; i++) {
				configurationValues[i].get().print_info();
			}

			break;
		default:
			returnMessage.successCode = SuccessCode::UNKNOWN_COMMAND;
			break;

	}
	return returnMessage;

}

uint8_t CommandController_Configuration::getCategoryID() {
	return static_cast<uint8_t>(CommandCategory::CONFIGURATION);
}

std::pair<uint8_t, uint8_t> CommandController_Configuration::getParameterLimits(uint8_t command_id) {
	switch (static_cast<FlashCommand>(command_id)) {
		case SET_VALUE:
			return {1, 5};
		case GET_VALUE:
		case GET_TYPE:
			return {1, 1};
		case LOAD:
		case STORE:
		case PRINT_ALL:
			return {0, 0};
		default:
			return {255, 255};

	}
}


CommandController_Configuration::CommandController_Configuration(std::reference_wrapper<BaseConfigurationValue> *configurationValues,
                                                                 size_t configurationValueCount) : configurationValues(
		configurationValues), configuration_value_count(configurationValueCount) {
	bool isFirstRun = BaseConfigurationValue::isFirstRun();
	for (size_t i = 0; i < configuration_value_count; i++) {
		if (isFirstRun) {
			configurationValues[i].get().store();
		} else {
			configurationValues[i].get().load();
		}
	}

	if(isFirstRun) {
		BaseConfigurationValue::removeFirstRun();
	}

}


