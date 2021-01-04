#include <core/display/DisplayController.hpp>
#include <cstdio>

DisplayController::DisplayController(BaseDisplayBoundary &displayBoundary, PMSVSettings &pmsvSettings)
        : displayBoundary(displayBoundary), pmsvSettings(pmsvSettings) {}

void DisplayController::update() {
    bool dirty = false;
    if (last_robot_id != pmsvSettings.robot_id) {
        dirty = true;
        last_robot_id = pmsvSettings.robot_id;
    }


    if (dirty) {
        display();
    }
    displayBoundary.update();
}

void DisplayController::display() {
    displayBoundary.clear();

    auto robot_id = (char *) "Robot ID:";
    char numberstring[4];
    sprintf(numberstring, "%d", static_cast<int>(pmsvSettings.robot_id));

    displayBoundary.write(robot_id);
    displayBoundary.write(numberstring);
    displayBoundary.newline();

}
