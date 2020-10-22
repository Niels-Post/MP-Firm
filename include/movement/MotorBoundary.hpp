#pragma once

#include <cstdint>
#include "AccelStepper.h"


/**
 * A boundary used for a single Stepper Motor
 */
class MotorBoundary {
    /// Stepper motor object that is used to move the motor
    AccelStepper stepper;
public:
    /**
     * Create a MotorBoundary
     *
     * The constructor automatically creates the underlying AccelStepper object
     * @param enable_pin Pin number connected to the enable pin of the stepper driver
     * @param step_pin Pin number connected to the step pin of the stepper driver
     * @param dir_pin Pin number connected to the dir pin of the stepper driver
     * @param steps_per_mm The number of steps a motor steps fo moving a millimeter
     */
    MotorBoundary(uint8_t enable_pin, uint8_t step_pin, uint8_t dir_pin, uint8_t steps_per_mm);

    /**
     * Start a movement of a specified amount of steps
     *
     * Note that the method returns before the movement is started. Movement is continued in the update() method.
     * @param steps The amount of steps to move
     * @return True if the starting of the movement was successful
     */
    bool startMoveSteps(uint16_t steps);

    /**
     * Stop all movement currently being processed
     */
    void halt();

    /**
     * Update the movement currently being processed.
     * Usually steps the motor at least once
     */
    void update();
};