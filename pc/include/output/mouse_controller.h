#pragma once

#include "types/input_packet.h"
#include "types/screen_point.h"

namespace Output {

    class MouseController {
    public:
        void handle(const Input::InputPacket& packet, const ScreenPoint& point);

    private:
        bool isDown = false;

        void move(const ScreenPoint& point) const;

        void mouseUp();
        void mouseDown();
    };
}
