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

#include <core/configuration/ConfigurationValue.hpp>
#include <core/PMSVSettings.hpp>
#include <communication/communicationboundary/NRF24Configuration.hpp>
#include <movement/motorboundary/AccelStepperConfig.hpp>
#include <communication/commandcontroller/CommandController_Configuration.hpp>
#include <communication/communicationboundary/NRF24CommunicationBoundary.hpp>
#include <movement/motorboundary/MotorBoundary_AccelStepper.hpp>
#include <core/movement/MovementController.hpp>
#include <communication/commandcontroller/CommandController_General.hpp>
#include <communication/commandcontroller/CommandController_Measurement.hpp>
#include <communication/commandcontroller/CommandController_Action.hpp>
#include <core/communication/CommunicationController.hpp>
#include <core/display/DisplayController.hpp>

#include <core/util/ArraySize.hpp>
#include <display/DisplayBoundary_SSD1306.hpp>


#include <utility>


////##################################################################   Configuration ###################################
PMSVSettings default_settings{
        0,
        1.434684f,
        1.4545f,
        0,
        180
};

auto c_robot_id = registerConfig("ROBOT_ID", default_settings.robot_id);

auto c_rot_per_mm = registerConfig("MOTOR_ROTATION_PER_MM_DISTANCE",
                                   default_settings.motor_rotation_degrees_per_mm_distance);
auto c_mm_per_rot = registerConfig("MM_DISTANCE_PER_ROBOT_ROTATION",
                                   default_settings.mm_distance_per_robot_rotation_degree);
auto c_min_speed = registerConfig("MIN_SPEED", default_settings.min_speed);
auto c_max_speed = registerConfig("MAX_SPEED", default_settings.max_speed);

NRFConfiguration nrf_config{
        RF24_PA_MAX,
        0x10,
        0xE0E0F1F1FFLL,
        0xE0E0F1F1FFLL,
        true,
        32,
        5,
        4
};

auto c_nrf_channel = registerConfig("NRF_CHANNEL", nrf_config.channel);
auto c_nrf_dynamicpayload = registerConfig("NRF_ENABLE_DYNAMICPAYLOAD", nrf_config.enable_dynamic_payload_length);
auto c_nrf_pin_ce = registerConfig("NRF_PIN_CE", nrf_config.pin_ce);
auto c_nrf_pin_csn = registerConfig("NRF_PIN_CSN", nrf_config.pin_csn);

AccelStepperConfig leftMotorConfig{
        12,
        11,
        13,
        10,
        9,
        4.44,
        false
};

auto c_leftmotor_pin_ms1 = registerConfig("LEFTMOTOR_PIN_MS1", leftMotorConfig.pin_ms1);
auto c_leftmotor_pin_ms2 = registerConfig("LEFTMOTOR_PIN_MS2", leftMotorConfig.pin_ms2);
auto c_leftmotor_pin_enable = registerConfig("LEFTMOTOR_PIN_ENABLE", leftMotorConfig.pin_enable);
auto c_leftmotor_pin_step = registerConfig("LEFTMOTOR_PIN_STEP", leftMotorConfig.pin_step);
auto c_leftmotor_pin_dir = registerConfig("LEFTMOTOR_PIN_DIR", leftMotorConfig.pin_dir);
auto c_leftmotor_steps_per_degree = registerConfig("LEFTMOTOR_STEPS_PER_DEGREE", leftMotorConfig.steps_per_degree);
auto c_leftmotor_forward_direction = registerConfig("LEFTMOTOR_FORWARD_DIRECTION", leftMotorConfig.forward_direction);

AccelStepperConfig rightMotorConfig{
        7,
        6,
        8,
        3,
        2,
        4.44,
        false
};


auto c_RIGHTmotor_pin_ms1 = registerConfig("RIGHTMOTOR_PIN_MS1", rightMotorConfig.pin_ms1);
auto c_RIGHTmotor_pin_ms2 = registerConfig("RIGHTMOTOR_PIN_MS2", rightMotorConfig.pin_ms2);
auto c_RIGHTmotor_pin_enable = registerConfig("RIGHTMOTOR_PIN_ENABLE", rightMotorConfig.pin_enable);
auto c_RIGHTmotor_pin_step = registerConfig("RIGHTMOTOR_PIN_STEP", rightMotorConfig.pin_step);
auto c_RIGHTmotor_pin_dir = registerConfig("RIGHTMOTOR_PIN_DIR", rightMotorConfig.pin_dir);
auto c_RIGHTmotor_steps_per_degree = registerConfig("RIGHTMOTOR_STEPS_PER_DEGREE", rightMotorConfig.steps_per_degree);
auto c_RIGHTmotor_forward_direction = registerConfig("RIGHTMOTOR_FORWARD_DIRECTION",
                                                     rightMotorConfig.forward_direction);



SSD1306Configuration displayConfiguration {
    128,
    32,
    53,
    59,
    49,
    51
};


std::reference_wrapper<BaseConfigurationValue> configurationValues[]{
        c_robot_id,
        c_rot_per_mm,
        c_mm_per_rot,
        c_min_speed,
        c_max_speed,
        c_nrf_channel,
        c_nrf_dynamicpayload,
        c_nrf_pin_ce,
        c_nrf_pin_csn,
        c_leftmotor_pin_ms1,
        c_leftmotor_pin_ms2,
        c_leftmotor_pin_enable,
        c_leftmotor_pin_step,
        c_leftmotor_pin_dir,
        c_leftmotor_steps_per_degree,
        c_leftmotor_forward_direction,
        c_RIGHTmotor_pin_ms1,
        c_RIGHTmotor_pin_ms2,
        c_RIGHTmotor_pin_enable,
        c_RIGHTmotor_pin_step,
        c_RIGHTmotor_pin_dir,
        c_RIGHTmotor_steps_per_degree,
        c_RIGHTmotor_forward_direction
};


//##################################################################   End Configuration ###############################




void setup() {
    Serial.begin(9600);

//        Set up Boundaries
    CommandController_Configuration configurationCommandController{configurationValues, lengthof(configurationValues)};

    NRF24CommunicationBoundary nrfBoundary{nrf_config, default_settings};

    MotorBoundary_AccelStepper leftMotor{leftMotorConfig};

    MotorBoundary_AccelStepper rightMotor{rightMotorConfig};

    MovementController movementController{leftMotor, rightMotor, default_settings};

    DisplayBoundary_SSD1306 displayBoundary{displayConfiguration, default_settings};

    DisplayController displayController{displayBoundary, default_settings};


    CommandController_General generalCommandHandler{default_settings, c_robot_id};
    CommandController_Action actionCommandHandler{movementController};
    CommandController_Measurement measurementCommandHandler{};


    std::reference_wrapper<BaseCommandController> commandControllers[] = {
            generalCommandHandler,
            actionCommandHandler,
            measurementCommandHandler,
            configurationCommandController
    };


    CommunicationController communicationController{nrfBoundary, commandControllers, lengthof(commandControllers)};
    volatile bool _true = true;

    while (_true) {
        movementController.update();
        communicationController.update();
        displayController.update();
    }

}

void loop() {
}


