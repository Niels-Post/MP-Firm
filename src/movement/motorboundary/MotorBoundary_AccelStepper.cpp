#include <movement/motorboundary/MotorBoundary_AccelStepper.hpp>

void MotorBoundary_AccelStepper::halt() {
    stepper.stop();
    stepper.disableOutputs();
}

void MotorBoundary_AccelStepper::update() {
    if (stepper.distanceToGo() != 0) {
        stepper.run();
    } else {
        stepper.disableOutputs();
    }
}

MotorBoundary_AccelStepper::MotorBoundary_AccelStepper(AccelStepperConfig &_config)
        : config(_config), stepper(stepper.DRIVER,
                  config.pin_step, config.pin_dir) {
    stepper.setEnablePin(config.pin_enable);
    stepper.setPinsInverted(false, false, true);

    pinMode(config.pin_ms1, OUTPUT);
    digitalWrite(config.pin_ms1, LOW);
    pinMode(config.pin_ms2, OUTPUT);
    digitalWrite(config.pin_ms2, LOW);
}

void MotorBoundary_AccelStepper::setDirection(bool dir) {
    rotateDirection = dir ^ !config.forward_direction;
}

bool MotorBoundary_AccelStepper::startMoveDegrees(uint16_t degree) {
    long stepsToMove = degree * config.steps_per_degree;
    if (!rotateDirection) {
        stepsToMove *= -1;
    }
    stepper.move(stepsToMove);
    stepper.enableOutputs();
    return true;

}

bool MotorBoundary_AccelStepper::isMoving() {
    return stepper.distanceToGo() != 0;
}

void MotorBoundary_AccelStepper::setMaxSpeed(float max_degrees_per_second) {
    stepper.setMaxSpeed(max_degrees_per_second * config.steps_per_degree * 10);
    stepper.setAcceleration(max_degrees_per_second * config.steps_per_degree);
}


