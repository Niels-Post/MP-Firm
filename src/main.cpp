#include <Arduino.h>

#define R_SENSE 0.11f
constexpr uint32_t steps_per_mm = 80;

#include <entity/PMSVSettings.hpp>
#include <boundary/communication/commandboundary/NRFBoundary.hpp>
#include <boundary/movement/StepperBoundary/AccelStepperBoundary.hpp>
#include <controller/MovementController.hpp>
#include <controller/CommunicationController.hpp>
#include <controller/CommandCategoryController/GeneralCommandController.hpp>
#include <controller/CommandCategoryController/ActionCommandController.hpp>
#include <controller/CommandCategoryController/MeasurementCommandController.hpp>


static const PMSVSettings default_settings(
        0,
        0,
        false,
        false,
        0,
        0,
        RF24_PA_LOW,
        50,
        0xE0E0F1F1E0LL,
        0xE0E0F1F1E4LL,
        true,
        32,
        false,
        5,
        4,
        {13, 10, 9, 80},
        {8, 3, 2, 80});


void setup() {
    Serial.begin(9600);

    //    Set up Boundaries
    NRFBoundary nrfBoundary{
            default_settings.nrf_pin_ce,
            default_settings.nrf_pin_csn,
            default_settings.nrf_channel,
            default_settings.nrf_readingpipe,
            default_settings.nrf_writingpipe,
            default_settings.nrf_enable_autoack,
            default_settings.nrf_enable_dynamicpayloads,
            default_settings.nrf_payload_size,
            default_settings.nrf_palevel,
    };

    AccelStepperBoundary leftMotor{
            default_settings.leftMotor.pin_enable,
            default_settings.leftMotor.pin_step,
            default_settings.leftMotor.pin_dir,
            default_settings.leftMotor.steps_per_mm,
    };

    AccelStepperBoundary rightMotor{
            default_settings.rightMotor.pin_enable,
            default_settings.rightMotor.pin_step,
            default_settings.rightMotor.pin_dir,
            default_settings.rightMotor.steps_per_mm,
    };

    MovementController movementController{leftMotor, rightMotor, default_settings};


    GeneralCommandController generalCommandHandler{};
    ActionCommandController      actionCommandHandler{movementController};
    MeasurementCommandController measurementCommandHandler{};

    CommandCategoryController *commandCategoryHandlers[] = {
            &generalCommandHandler,
            &actionCommandHandler,
            &measurementCommandHandler
    };

    CommunicationController<20, array_size(commandCategoryHandlers)> communicationController{nrfBoundary, commandCategoryHandlers};

    volatile bool _true = true;
    while (_true) {
        movementController.update();
        communicationController.update();
    }

}

void loop() {
}


