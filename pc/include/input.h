#pragma once

#include<windows.h>

#include"types/screen_point.h"

/**
 * @brief Input handling for mouse control.
 */
namespace Input {

    /**
     * @brief Move the mouse cursor to absolute Windows mouse coordinates.
     * 
     * @param point Absolute Windows mouse coordinates.
     */
    void moveMouse(Common::ScreenPoint point);

    /**
     * @brief Mouse button down.
     */
    void mouseDown();

    /**
     * @brief Mouse button up.
     */
    void mouseUp();
}