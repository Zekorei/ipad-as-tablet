#pragma once

#include<windows.h>

/**
 * @brief Initialize screen metrics for Windows display scaling.
 */
void initScreenMetrics();

/**
 * @brief Move the mouse cursor to normalized coordinates
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
