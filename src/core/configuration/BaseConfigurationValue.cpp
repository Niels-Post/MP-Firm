#include <core/configuration/BaseConfigurationValue.hpp>
#include <core/configuration/ConfigurationValue.hpp>


DueFlashStorage BaseConfigurationValue::storage;

bool BaseConfigurationValue::isFirstRun() {
    return storage.read(0) != 0;
}

void BaseConfigurationValue::removeFirstRun() {
    storage.write(0, 0);
}

uint8_t BaseConfigurationValue::getId() {
    return CONFIG_ID;
}

BaseConfigurationValue::BaseConfigurationValue(const char *configName, uint8_t size) : CONFIG_NAME(configName) {
    static uint8_t current_id = 0;
    static uint8_t current_address = 4;
    current_id ++;
    current_address = (current_address + 3) & ~0x3;
    ADDRESS_START = current_address;
    CONFIG_ID = current_id;
    current_address += size;
}



void BaseConfigurationValue::print_info() {
    Serial.print(CONFIG_ID);
    Serial.print(": ");
    Serial.print(CONFIG_NAME);
    Serial.print(", Address: ");
    Serial.println(ADDRESS_START);
}

void BaseConfigurationValue::store() {
    auto data = get();
    storage.write(ADDRESS_START, (uint8_t *) data.first, data.second);
}

void BaseConfigurationValue::load() {

    uint8_t *flash_data = storage.readAddress(ADDRESS_START);
    set(flash_data);
}

const char *BaseConfigurationValue::get_name() {
    return CONFIG_NAME;
}
