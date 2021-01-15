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

#pragma once

#include <cstdint>
#include <DueFlashStorage.h>
#include <core/util/ArduinoSafe.hpp>
#include <utility>

class BaseConfigurationValue {
protected:
    /// Name of the configuration value
    const char* CONFIG_NAME;
    /// ID, used by configuration commands
    uint8_t CONFIG_ID = 0;
    /// ROM address to store the variable at, only used internally
    uint8_t ADDRESS_START = 0;
    /// Instance of DueFlashStorage to use while writing
    static DueFlashStorage storage;


public:
    /**
     * Construct a configuration value
     *
     * This constructor also allocates space in flash memory for the value
     * @param configName name of the value
     * @param size size of the value in bytes
     */
    BaseConfigurationValue(const char *configName, uint8_t size);

    /**
     * Disable the copy constructor, since this would likely cause strange behaviour
     * @return
     */
    BaseConfigurationValue(const BaseConfigurationValue&);


    /**
     * Check if this is the first time the software is started since flashing it.
     *
     * If it is the first time, the configuration needs to be written to flash
     * @return
     */
    static bool isFirstRun();

    /**
     * Remove the first run modifier.
     */
    static void removeFirstRun();

    /**
     * Get the ID of this configuration value.
     *
     * The ID is automatically, sequentially generated
     * Note that this does not equate to a flash address.
     * @return
     */
    uint8_t  getId();

    /**
     * Get a character representing the type of the Value, eg 'b' for a boolean value
     * @return The type char
     */
    virtual char getType() = 0;

    /**
     * Set the value
     * @param origin Address of the value to copy
     */
    virtual void set(void *origin) = 0;

    /**
     * Get the bytes of the value
     * @return A pair consisting of a pointer to the start address and the size of the value
     */
    virtual std::pair<void*, uint8_t> get() = 0;

    /**
     * Print information about the value: The flash address, identifier and name
     */
    void print_info();

    /**
     * Store the value to flash
     */
    void store();

    /**
     * Load the value from flash
     */
    void load();

    /**
     * Get the name of the configuration parameter
     */
     const char * get_name();
};