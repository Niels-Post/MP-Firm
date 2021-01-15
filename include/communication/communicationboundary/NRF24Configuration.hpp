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
    /// CE pin the NRF is connected to
    uint8_t pin_ce;
    /// CSN pin the NRF is connected to
    uint8_t pin_csn;
};
