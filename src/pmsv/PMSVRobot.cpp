//
// Created by Niels on 13/10/2020.
//

#include <pmsv/PMSVRobot.hpp>


PMSVRobot::PMSVRobot(const PMSVSettings &settings)
        : movementController(settings), communicationController(settings, movementController), settings(settings) {
}

void PMSVRobot::update() {
    communicationController.update();
    movementController.update();
}
