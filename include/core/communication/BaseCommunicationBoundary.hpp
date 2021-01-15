/*
 * Copyright (c) 2021. Niels Post. AI Lab Vrije Universiteit Brussel.
 *
 * This file is part of MP-Firm.
 *
 * MP-Firm is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * MP-Firm is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with MP-Firm.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once


#include <core/communication/Response.hpp>
#include <core/communication/Command.hpp>

/**
 * The MessageBoundary is a boundary used for transmitting and receiving commands.
 * The MessageBoundary can be extended and implemented for use with various communication methods, wireless or wired.
 *
 * It is assumed that communication is two way between 1 controller and 1 robot (it is not a busline)
 */
class BaseCommunicationBoundary {
public:
    /**
     * Transmit a returncommand to the Controller
     * @param command The command to send
     */
    virtual bool sendMessage(const Response &command) = 0;

    /**
     * Should check if a command from the controller was received or is available
     */
    virtual bool isMessageAvailable() = 0;

    /**
     * Parse and return the next received command
     *
     * This method should use Command::validate to make sure a command is valid, and then use Command::parse to parse the data.
     */
    virtual Command getNextMessage() = 0;

};