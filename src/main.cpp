


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

#include <utility>

#define R_SENSE 0.11f


//##################################################################   Configuration ###################################
PMSVSettings default_settings{
        0,
        1.434684f,
        1.4545f,
        0,
        180
};

auto c_rot_per_mm = registerConfig("MOTOR_ROTATION_PER_MM_DISTANCE",
                                   default_settings.motor_rotation_degrees_per_mm_distance);
auto c_mm_per_rot = registerConfig("MM_DISTANCE_PER_ROBOT_ROTATION",
                                   default_settings.mm_distance_per_robot_rotation_degree);
auto c_min_speed = registerConfig("MIN_SPEED", default_settings.min_speed);
auto c_max_speed = registerConfig("MAX_SPEED", default_settings.max_speed);

NRFConfiguration nrf_config{
        RF24_PA_HIGH,
        50,
        0xE0E0F1F1E4LL,
        0xE0E0F1F1E4LL,
        true,
        32,
        true,
        5,
        4
};

auto c_nrf_channel = registerConfig("NRF_CHANNEL", nrf_config.channel);
auto c_nrf_dynamicpayload = registerConfig("NRF_ENABLE_DYNAMICPAYLOAD", nrf_config.enable_dynamic_payload_length);
auto c_nrf_autoack = registerConfig("NRF_ENABLE_AUTOACK", nrf_config.enable_autoack);
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


std::reference_wrapper<BaseConfigurationValue> configurationValues[]{
        c_rot_per_mm,
        c_mm_per_rot,
        c_min_speed,
        c_max_speed,
        c_nrf_channel,
        c_nrf_dynamicpayload,
        c_nrf_autoack,
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

    //    Set up Boundaries
    CommandController_Configuration flashCommandController{configurationValues, 23};

    NRF24CommunicationBoundary nrfBoundary{nrf_config};

    MotorBoundary_AccelStepper leftMotor{leftMotorConfig};

    MotorBoundary_AccelStepper rightMotor{rightMotorConfig};

    MovementController movementController{leftMotor, rightMotor, default_settings};


    CommandController_General generalCommandHandler{};
    CommandController_Action actionCommandHandler{movementController};
    CommandController_Measurement measurementCommandHandler{};


    std::reference_wrapper<BaseCommandController> commandControllers[] = {
            generalCommandHandler,
            actionCommandHandler,
            measurementCommandHandler,
            flashCommandController
    };


    CommunicationController communicationController{nrfBoundary, commandControllers, 4};
    Serial.println("Init done");
    volatile bool _true = true;
    while (_true) {
        movementController.update();
        communicationController.update();
    }

}

void loop() {
}


