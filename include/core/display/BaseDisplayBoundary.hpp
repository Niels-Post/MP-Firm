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
#include <cstdint>

/**
 * Boundary class for a text display.
 */
class BaseDisplayBoundary {
public:
    /**
     * SetCursor should set the write cursor to the specified position (in characters)
     * @param x X position (position within a line)
     * @param y Y Position (row number)
     */
    virtual void setCursor(uint8_t x, uint8_t y) = 0;

    /**
     * Change the cursor to the start of the screen
     */
    void resetCursor() {
        setCursor(0,0);
    }

    /**
     * Write a given string to the display
     *
     * When called consecutively, strings should appear after each other
     * @param str Null terminated string to print
     */
    virtual void write(char * str) = 0;

    /**
     * End the current line and set the cursor to the start of the next line
     */
    virtual void newline() = 0;

    /**
     * Clear the entire display and reset the cursor
     */
    virtual void clear() = 0;


    /**
     * Can be used in case a display needs to be updated continuously
     */
    virtual void update() = 0;
};