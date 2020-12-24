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
	char getType() override {
		return _type.letter;
	}

private:

	void set(void *origin) override {
		value = *((T *) origin);
	}

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
