//
// Created by Niels on 21/10/2020.
//

#include <boundary/movement/StepperBoundary/AccelStepperBoundary.hpp>

bool AccelStepperBoundary::startMoveSteps(uint16_t steps) {
    long tomove = steps;
    if (!direction) {
        tomove *= -1;
    }
    Serial.println(tomove);
    stepper.move(tomove);
    stepper.enableOutputs();
    return false;
}

void AccelStepperBoundary::halt() {
    stepper.stop();
    stepper.disableOutputs();
}

void AccelStepperBoundary::update() {
    if (stepper.distanceToGo() != 0) {
        stepper.run();
    } else {
        stepper.disableOutputs();
    }
}

AccelStepperBoundary::AccelStepperBoundary(uint8_t enable_pin, uint8_t step_pin, uint8_t dir_pin, uint8_t steps_per_mm)
        : stepper(stepper.DRIVER,
                  step_pin, dir_pin), stepsPerMM(steps_per_mm) {
    stepper.setMaxSpeed(50 * steps_per_mm);
    stepper.setAcceleration(1000 * steps_per_mm);
    stepper.setEnablePin(enable_pin);
    stepper.setPinsInverted(false, false, true);
//    stepper.enableOutputs();
}

void AccelStepperBoundary::setDirection(bool dir) {
    direction = dir;
}

bool AccelStepperBoundary::startMoveMM(uint16_t mm) {
    return startMoveSteps(mm * stepsPerMM);

}

