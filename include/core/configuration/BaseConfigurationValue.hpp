#pragma once

#include <cstdint>
#include <DueFlashStorage.h>
#include <core/util/ArduinoSafe.hpp>
#include <utility>

class BaseConfigurationValue {
protected:
    const char* CONFIG_NAME;
    uint8_t CONFIG_ID = 0;
    uint8_t ADDRESS_START = 0;
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