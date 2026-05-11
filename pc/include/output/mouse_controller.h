#pragma once

#include"types/input_packet.h"
#include"types/screen_point.h"

namespace Output {

    class MouseController {
    public:
        void handle(const Input::InputPacket& packet, const Common::ScreenPoint& point);

    private:
        bool isDown = false;

        void move(const Common::ScreenPoint& point) const;

        void mouseUp();
        void mouseDown();
    };
}
