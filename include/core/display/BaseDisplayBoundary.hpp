#pragma once
#include <cstdint>
class BaseDisplayBoundary {

public:
    /**
     * SetCursor should set the write cursor to the specified position (in characters)
     * @param x X position (position within a line)
     * @param y Y Position (row number)
     */
    virtual void setCursor(uint8_t x, uint8_t y) = 0;

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