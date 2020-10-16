#include <Arduino.h>
#include <pmsv/PMSVSettings.hpp>
#include <pmsv/PMSVRobot.hpp>

//
//


//

void setup() {
    Serial.begin(9600);

    PMSVSettings default_settings(
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
            10);

    PMSVRobot robot(default_settings);


    volatile bool _true = true;
    while(_true) {
        robot.update();
    }

}

void loop() {
}


