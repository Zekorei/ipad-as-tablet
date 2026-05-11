#pragma once

#include<cstdint>

namespace Input {

    struct InputPacket {
        float x;
        float y;
        float pressure;
        uint8_t flags;
        uint64_t timestamp;
    };
}
