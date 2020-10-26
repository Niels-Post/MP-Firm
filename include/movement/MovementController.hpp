#pragma once

#include <movement/MotorBoundary.hpp>
#include <communication/command/ReturnCommand.hpp>

class PMSVSettings;

class MovementController {
    /// Boundary for the motor on the right side of the robot
    MotorBoundary leftMotor;
    /// Boundary for the motor on the right side of the robot
    MotorBoundary rightMotor;
    /// Reference to the settings object to use to convert values
    const PMSVSettings &settings;

    /**
     * Try to move both motors a given amount of steps. (Internal use only)
     *
     * @param steps The amount of steps to move the motors
     * @return  a ReturnCode determining if the start was successful
     */
    ReturnCode tryMoveSteps(long steps);

public:
    /**
     * Change the speed of movement.
     *
     * Affects movements currently being made
     * @param speed New speed of movement
     * @return
     */
    ReturnCode setSpeed(uint16_t speed);

    /**
     * Change the direction of movement
     *
     * Does not affect direction of movements currently being made
     * @param dir New direction, true being forward, and false backward
     * @return
     */
    ReturnCode setDirection(bool dir);

    /**
     * Start a movement of a specified distance
     *
     * @param cm Distance in CM
     * @return
     */
    ReturnCode startMoveCM(uint16_t cm);

    /**
     * Start a movement by moving motors a specified amount of steps
     * @param steps The amount of steps to move
     * @return
     */
    ReturnCode startMoveSteps(uint16_t steps);

    /**
     * Start a rotation of a specified angle
     * @param degrees The angle to rotate
     * @param rotate_direction The rotation direction (true for right, false for left)
     * @return
     */
    ReturnCode startRotateDegrees(uint16_t degrees, bool rotate_direction);

    /**
     * Start a rotation by moving motors a specified amount of steps in opposite direction
     * @param steps The amount of steps to move each motor
     * @param rotate_direction The rotation direction (true for right, false for left)
     * @return
     */
    ReturnCode startRotateSteps(uint16_t steps, bool rotate_direction);

    /**
     * Stop all movements currently being made
     * @return
     */
    ReturnCode halt();

    /**
     * Update function for the movementcontroller.
     * Should be called often to be able to step motors properly
     */
    void update();

    /**
     * Create a MovementController
     *
     * Initializes both Motors using the settings object
     * @param pmsvSettings
     */
    MovementController(const PMSVSettings &pmsvSettings);
};