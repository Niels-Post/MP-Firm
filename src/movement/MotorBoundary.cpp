//
// Created by Niels on 21/10/2020.
//

#include <movement/MotorBoundary.hpp>

bool MotorBoundary::startMoveSteps(uint16_t steps) {
    stepper.move(steps);
    stepper.enableOutputs();
    return false;
}

void MotorBoundary::halt() {
    stepper.stop();
    stepper.disableOutputs();
}

void MotorBoundary::update() {
    if (stepper.distanceToGo() > 0) {
        stepper.run();
    } else {
        stepper.disableOutputs();
    }
}

MotorBoundary::MotorBoundary(uint8_t enable_pin, uint8_t step_pin, uint8_t dir_pin, uint8_t steps_per_mm)
        : stepper(stepper.DRIVER,
                  step_pin, dir_pin) {
    stepper.setMaxSpeed(50 * steps_per_mm);
    stepper.setAcceleration(1000 * steps_per_mm);
    stepper.setEnablePin(enable_pin);
    stepper.setPinsInverted(false, false, true);
    stepper.enableOutputs();
}

