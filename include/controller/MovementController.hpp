#pragma once

#include <entity/RobotMessage.hpp>
#include <boundary/movement/MotorBoundary.hpp>

class PMSVSettings;

class MovementController {
    /// Boundary for the motor on the right side of the robot
    MotorBoundary &leftMotor;
    /// Boundary for the motor on the right side of the robot
    MotorBoundary &rightMotor;
    /// Reference to the settings object to use to convert values
    const PMSVSettings &settings;

    SuccessCode tryMoveMM(uint16_t mm) const;
public:
    /**
     * Change the speed of movement.
     *
     * Affects movements currently being made
     * @param speed New speed of movement
     * @return
     */
    SuccessCode setSpeed(uint16_t speed);

    /**
     * Change the direction of movement
     *
     * Does not affect direction of movements currently being made
     * @param dir New direction, true being forward, and false backward
     * @return
     */
    SuccessCode setDirection(bool dir);

    /**
     * Start a movement of a specified distance
     *
     * @param mm Distance in CM
     * @return
     */
    SuccessCode startMoveMM(uint16_t mm);

    /**
     * Start a rotation of a specified angle
     * @param degrees The angle to rotate
     * @param rotate_direction The rotation direction (true for right, false for left)
     * @return
     */
    SuccessCode startRotateDegrees(uint16_t degrees, bool rotate_direction);

    /**
     * Stop all movements currently being made
     * @return
     */
    SuccessCode halt();

    /**
     * Update function for the movementcontroller.
     * Should be called often to be able to step motors properly
     */
    void update();

    MovementController(MotorBoundary &leftMotor, MotorBoundary &rightMotor, const PMSVSettings &settings);


};