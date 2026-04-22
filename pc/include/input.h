#pragma once

#include<windows.h>

#include<types.h>

/**
 * @brief Input handling for mouse control.
 */
namespace Input {

    /**
     * @brief Move the mouse cursor to normalized coordinates.
     * 
     * Coverts a coordinate in the range `[0, 1]` to absolute screen coordinates and moves the mouse cursor there.
     * 
     * @param point Normalized input coordinates (0.0 to 1.0)
     */
    void moveMouse(Common::NormalizedPoint point);

    /**
     * @brief Mouse button down.
     */
    void mouseDown();

    /**
     * @brief Mouse button up.
     */
    void mouseUp();
}