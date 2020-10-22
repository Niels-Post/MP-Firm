#include <Arduino.h>
#include <pmsv/PMSVSettings.hpp>
#include <pmsv/PMSVRobot.hpp>





#define R_SENSE 0.11f
constexpr uint32_t steps_per_mm = 80;


#include <AccelStepper.h>


//void setup() {
//    SPI.begin();
//    Serial.begin(9600);
//    while (!Serial);
//    Serial.println("Start...");
//
//    stepper.setMaxSpeed(50 * steps_per_mm); // 100mm/s @ 80 steps/mm
//    stepper.setAcceleration(1000 * steps_per_mm); // 2000mm/s^2
//    stepper.setEnablePin(EN_PIN);
//    stepper.setPinsInverted(false, false, true);
//    stepper.enableOutputs();
//
//    stepper2.setMaxSpeed(50 * steps_per_mm); // 100mm/s @ 80 steps/mm
//    stepper2.setAcceleration(1000 * steps_per_mm); // 2000mm/s^2
//    stepper2.setEnablePin(EN_PIN_2);
//    stepper2.setPinsInverted(true, false, true);
//    stepper2.enableOutputs();
//
//}
//
//void loop() {
//    if (stepper.distanceToGo() == 0) {
//        stepper.disableOutputs();
//        delay(100);
//        stepper.move(100 * steps_per_mm); // Move 100mm
//        stepper.enableOutputs();
//    }
//    stepper.run();
//
//
//    if (stepper2.distanceToGo() == 0) {
//        stepper2.disableOutputs();
//        delay(100);
//        stepper2.move(100 * steps_per_mm); // Move 100mm
//        stepper2.enableOutputs();
//    }
//    stepper2.run();
//}

static const PMSVSettings default_settings(
        0,
        0,
        false,
        false,
        0,
        0,
        RF24_PA_HIGH,
        50,
        0xE0E0F1F1E0LL,
        0xE0E0F1F1E4LL,
        true,
        32,
        false,
        9,
        10,
        {12, 5, 4, 80},
        {11, 31, 30, 80});


void setup() {
    Serial.begin(9600);



    PMSVRobot robot(default_settings);


    volatile bool _true = true;
    while (_true) {
        robot.update();
    }

}

void loop() {
}


