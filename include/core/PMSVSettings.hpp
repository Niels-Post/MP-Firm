#pragma once

struct PMSVSettings {
    /// Robot Identifier. Should be set through the Configuration Commands
    uint8_t robot_id;
    /// How many degrees do both motors need to rotate before the robot moves 1 mm
    float motor_rotation_degrees_per_mm_distance;
    /// How far do both wheels need to rotate in opposite direction before the robot rotates 1 degree
    float mm_distance_per_robot_rotation_degree;
    /// Minimum speed for the robot
    float min_speed;
    /// Maximum speed for the robot
    float max_speed;
};

