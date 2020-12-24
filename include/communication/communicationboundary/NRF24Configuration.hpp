#pragma once

#include <RF24.h>

/**
 * All Configuration options for the NRF Boundary
 */
struct NRFConfiguration {
    /// The Power level to use: Options are RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX, RF24_PA_ERROR
    rf24_pa_dbm_e palevel;
    /// The channel to communicate over (should match the controller's channel)
    uint8_t channel;
    /// The base address for receiving commands. The last byte is replaced with the robot's id for receiving directed commands
    uint64_t base_reading_pipe;
    /// The base address for sending return values. The last byte is replaced with the robot's id.
    uint64_t base_writing_pipe;
    /// Should NRF packets be variable in length (false is currently unsupported)
    bool enable_dynamic_payload_length;
    /// Static payload length (currently unneeded since static payload is unsupported)
    uint8_t payload_size;
    /// Have the NRF module automatically acknowledge incoming messages (needs to match the controller's setting)
    bool enable_autoack;
    /// CE pin the NRF is connected to
    uint8_t pin_ce;
    /// CSN pin the NRF is connected to
    uint8_t pin_csn;
};
