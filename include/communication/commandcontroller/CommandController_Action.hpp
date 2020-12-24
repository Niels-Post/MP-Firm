#pragma once

#include <core/communication/BaseCommandController.hpp>

#include <core/movement/MovementController.hpp>

#include <core/communication/Response.hpp>
#include <core/communication/Command.hpp>

#include <cstdint>
#include <utility>


/**
 * Handles commands in the category \refitem{CommandCategory::ACTION}
 */
class CommandController_Action : public BaseCommandController {
    /// MovementController, used for performing movement actions
    MovementController &movementController;
public:
    /**
     * \copydoc BaseCommandController::handle(const Command&, ResponseCallback)
     */
    Response handle(const Command &cmd, ResponseCallback callback) override;

    /**
     * Construct the ActionCommandHandler
     * @param movementController The robot's movementController
     */
    CommandController_Action(MovementController &movementController);


    /**
     * \copydoc BaseCommandController::getCategoryID()
     */
    uint8_t getCategoryID() override;

    /**
     * \copydoc BaseCommandController::getParameterLimits(uint8_t)
     */
    std::pair<uint8_t, uint8_t> getParameterLimits(uint8_t command_id) override;
};
