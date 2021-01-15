#pragma once

#include <core/configuration/BaseConfigurationValue.hpp>

#include <utility>
#include <cstdint>

/**
 * Templated struct used to select the type character at compile time
 */
template<typename T>
struct type;

template<>
struct type<float> {
	const char letter = 'f';
};

template<>
struct type<int> {
	const char letter = 'i';
};

template<>
struct type<unsigned char> {
	const char letter = 'c';
};

template<>
struct type<bool> {
	const char letter = 'b';
};

/**
 * Templated ConfigurationValue.
 *
 * This class automatically takes care of setting, getting, storing and loading a value using its type.
 * @tparam T
 */
template <typename T>
class ConfigurationValue: public BaseConfigurationValue {
	T &value;
	type<T> _type;

public:
	ConfigurationValue(const char * name, T &value) : BaseConfigurationValue(name, sizeof(T)), value(value) {}

private:

public:
    /**
     * Get the type character of the value
     * may return:
     * f: 4 Byte float
     * i: 4 byte integer
     * c: 1 byte unsigned integer
     * b: 1 bit boolean
     * @return
     */
	char getType() override {
		return _type.letter;
	}

private:

    /**
     * Change the value of the configurationvalue
     * @param origin Address to read the value from
     */
	void set(void *origin) override {
		value = *((T *) origin);
	}

	/**
	 * Get the value of the configurationvalue
	 *
	 * @return A pair of a pointer to the value's address and the size of the value
	 */
	std::pair<void *, uint8_t> get() override {
		return {&value, sizeof(T)};
	}
};


/**
 * Register a configurationvalue without needing the template parameter
 * @param name Name of the configuration value
 * @param value Reference to the value to register
 * @return
 */
template<typename T>
ConfigurationValue<T> registerConfig(const char *name, T &value) {
	return ConfigurationValue<T>(name, value);
}
