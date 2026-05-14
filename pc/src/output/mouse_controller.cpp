#include"output/mouse_controller.h"
#include"protocol.h"

#include<windows.h>

namespace Output {

    void MouseController::handle(const Input::InputPacket& packet, const Common::ScreenPoint& point) {
        bool moveEvent = (packet.flags & Protocol::MOVE) != 0;
        bool downEvent = (packet.flags & Protocol::DOWN) != 0;
        bool upEvent = (packet.flags & Protocol::UP) != 0;

        if (moveEvent) move(point);
        if (downEvent && !isDown) mouseDown();
        if (upEvent && isDown) mouseUp();
    }

    void MouseController::move(const Common::ScreenPoint& point) const {
        INPUT input{};

        input.type = INPUT_MOUSE;
        input.mi.dx = point.x();
        input.mi.dy = point.y();
        input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;

        SendInput(1, &input, sizeof(input));
    }

    void MouseController::mouseUp() {
        INPUT input{};

        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_LEFTUP;

        isDown = false;

        SendInput(1, &input, sizeof(INPUT));
    }

    void MouseController::mouseDown() {
        INPUT input{};

        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

        isDown = true;

        SendInput(1, &input, sizeof(INPUT));
    }
}
