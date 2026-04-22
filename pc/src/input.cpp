#include<windows.h>
#include<iostream>
#include<cstdint>

#include"input.h"

/**
 * @brief Normalize coordinates to absolute screen coordinates by Windows convention.
 * @internal
 */
static void normalizeToAbsolute(const Common::NormalizedPoint& point, LONG &outX, LONG &outY) {
    outX = (LONG)(point.x * 65535.0f);
    outY = (LONG)(point.y * 65535.0f);
}

void Input::moveMouse(Common::NormalizedPoint point) {
#ifdef NDEBUG
    point.validate();
#endif

    INPUT input{};
    LONG dx, dy;

    input.type = INPUT_MOUSE;
    
    normalizeToAbsolute(point, dx, dy);

    input.mi.dx = dx;
    input.mi.dy = dy;
    input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;

    SendInput(1, &input, sizeof(INPUT));
}

void Input::mouseDown() {
    INPUT input{};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &input, sizeof(INPUT));
}

void Input::mouseUp() {
    INPUT input{};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, &input, sizeof(INPUT));
}
