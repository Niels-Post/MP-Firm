#pragma once

#include <communication/CommunicationController.hpp>
#include <movement/MovementController.hpp>
#include <pmsv/PMSVSettings.hpp>

class PMSVRobot {
    MovementController      movementController;
    CommunicationController communicationController;
    PMSVSettings            settings;


public:
    PMSVRobot(PMSVSettings &settings);

    void update();
};

