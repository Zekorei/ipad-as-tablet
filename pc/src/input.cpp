#include<windows.h>
#include<iostream>
#include<cstdint>

#include"input.h"

void Input::moveMouse(Common::ScreenPoint point) {
    INPUT input{};

    input.type = INPUT_MOUSE;
    input.mi.dx = point.x();
    input.mi.dy = point.y();
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
