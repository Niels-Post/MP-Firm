#pragma once

#include <cstdint>
#include <boundary/movement/MotorBoundary.hpp>
#include "AccelStepper.h"


/**
 * A boundary used for a single Stepper Motor
 */
class AccelStepperBoundary: public MotorBoundary {
    /// Stepper motor object that is used to move the motor
    AccelStepper stepper;
    bool     direction  = true;
    uint16_t stepsPerMM;
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
    AccelStepperBoundary(uint8_t enable_pin, uint8_t step_pin, uint8_t dir_pin, uint8_t steps_per_mm);

    /**
     * Start a movement of a specified amount of steps
     *
     * Note that the method returns before the movement is started. Movement is continued in the update() method.
     * @param steps The amount of steps to move
     * @return True if the starting of the movement was successful
     */
    bool startMoveSteps(uint16_t steps);

    bool startMoveMM(uint16_t mm) override;

    /**
     * Stop all movement currently being processed
     */
    void halt() override;

    /**
     * Update the movement currently being processed.
     * Usually steps the motor at least once
     */
    void update() override;

    /**
     * Change the direction this motor will rotate.
     *
     * Note: this does not change directions for movements that are already started
     * @param dir The new directin (true for forward, false for backward.
     */
    void setDirection(bool dir) override;

};