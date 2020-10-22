#pragma once

#include <communication/CommunicationController.hpp>
#include <movement/MovementController.hpp>
#include <pmsv/PMSVSettings.hpp>

class PMSVRobot {
    MovementController      movementController;
    CommunicationController communicationController;
    const PMSVSettings      &settings;


public:
    PMSVRobot(const PMSVSettings &settings);

    void update();
};

