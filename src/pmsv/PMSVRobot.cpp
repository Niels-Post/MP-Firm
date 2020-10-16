//
// Created by Niels on 13/10/2020.
//

#include <pmsv/PMSVRobot.hpp>


PMSVRobot::PMSVRobot(PMSVSettings &settings): movementController(), communicationController(settings, movementController),  settings(settings){
}

void PMSVRobot::update() {
    communicationController.update();
    movementController.update();
}
