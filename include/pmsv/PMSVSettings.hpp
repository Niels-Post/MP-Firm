#pragma once

#include <RF24.h>

class PMSVSettings {

public:
    // Settings related to the Movement Controller
    uint16_t steps_per_cm;
    uint16_t steps_per_degree;
    bool     left_motor_fwd;
    bool     right_motor_fwd;
    uint16_t min_speed;
    uint16_t max_speed;

    // Curve start_curve
    // Curve stop_curve


    // Settings related to NRF
    rf24_pa_dbm_e nrf_palevel;
    uint8_t       nrf_channel;
    uint64_t      nrf_readingpipe = 0xE0E0F1F1E0LL;
    uint64_t      nrf_writingpipe = 0xE0E0F1F1E4LL;
    bool          nrf_enable_dynamicpayloads;
    size_t        nrf_payload_size;
    bool          nrf_enable_autoack;

    uint8_t nrf_pin_ce;
    uint8_t nrf_pin_csn;


    PMSVSettings(uint16_t stepsPerCm, uint16_t stepsPerDegree, bool leftMotorFwd, bool rightMotorFwd, uint16_t minSpeed,
                 uint16_t maxSpeed, rf24_pa_dbm_e nrfPalevel, uint8_t nrfChannel, uint64_t nrfReadingpipe,
                 uint64_t nrfWritingpipe, bool nrfEnableDynamicpayloads, size_t nrfPacketSize, bool nrfEnableAutoack,
                 uint8_t nrfPinCe, uint8_t nrfPinCsn)
            : steps_per_cm(stepsPerCm),
              steps_per_degree(
                      stepsPerDegree),
              left_motor_fwd(
                      leftMotorFwd),
              right_motor_fwd(
                      rightMotorFwd),
              min_speed(minSpeed),
              max_speed(maxSpeed),
              nrf_palevel(nrfPalevel),
              nrf_channel(nrfChannel),
              nrf_readingpipe(
                      nrfReadingpipe), nrf_writingpipe(nrfWritingpipe),
              nrf_enable_dynamicpayloads(
                      nrfEnableDynamicpayloads),
              nrf_payload_size(
                      nrfPacketSize),
              nrf_enable_autoack(
                      nrfEnableAutoack),
              nrf_pin_ce(nrfPinCe), nrf_pin_csn(nrfPinCsn) {}

};

