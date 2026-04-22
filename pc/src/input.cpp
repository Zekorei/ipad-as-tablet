#include<windows.h>
#include<iostream>
#include<cstdint>

#include"input.h"

static int SCREEN_WIDTH = 0;
static int SCREEN_HEIGHT = 0;

void initScreenMetrics() {
    SCREEN_WIDTH = GetSystemMetrics(SM_CXSCREEN);
    SCREEN_HEIGHT = GetSystemMetrics(SM_CYSCREEN);
}

/**
 * @brief Normalize coordinates to absolute screen coordinates by Windows convention.
 * @internal
 */
static void normalizeToAbsolute(float x, float y, LONG &outX, LONG &outY) {
    outX = (LONG)(x * 65535.0f);
    outY = (LONG)(y * 65535.0f);
}

void moveMouse(float x, float y) {
    INPUT input{};
    input.type = INPUT_MOUSE;

    LONG dx, dy;
    normalizeToAbsolute(x, y, dx, dy);

    input.mi.dx = dx;
    input.mi.dy = dy;
    input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;

    SendInput(1, &input, sizeof(INPUT));
}

void mouseDown() {
    INPUT input{};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &input, sizeof(INPUT));
}

void mouseUp() {
    INPUT input{};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, &input, sizeof(INPUT));
}
