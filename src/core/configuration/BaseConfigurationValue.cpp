/*
 * Copyright (c) 2021. Niels Post. AI Lab Vrije Universiteit Brussel.
 *
 * This file is part of MP-Firm.
 *
 * MP-Firm is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * MP-Firm is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with MP-Firm.  If not, see <https://www.gnu.org/licenses/>.
 */

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
