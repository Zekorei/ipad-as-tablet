#pragma once

#include<windows.h>

/**
 * @brief Input handling for mouse control.
 */
namespace Input {}

    /**
     * @brief Initialize screen metrics for Windows display scaling.
     */
    void initScreenMetrics();

    /**
     * @brief Move the mouse cursor to normalized coordinates.
     * 
     * Coverts a coordinate in the range `[0, 1]` to absolute screen coordinates and moves the mouse cursor there.
     * 
     * @param x Normalized x coordinate `[0.0, 1.0]`.
     * @param y Normalized y coordinate `[0.0, 1.0]`.
     */
    void moveMouse(float x, float y);

    /**
     * @brief Mouse button down.
     */
    void mouseDown();

    /**
     * @brief Mouse button up.
     */
    void mouseUp();
}