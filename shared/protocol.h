#pragma once

#include<cstdint>

/**
 * @brief Shared protocol definitions between PC and iPad components on the PC side.
 */
namespace Protocol {
    
    /**
     * @brief Input flags for mouse events (bitmask).
     */
    enum Flags : uint8_t {
        DOWN = 0b00000001,
        MOVE = 0b00000010,
        UP   = 0b00000100
    };

    /**
     * @brief Packet which is sent from iPad to PC for each input event.
     * 
     * Must remain byte-compatible with the Swift implementation on the iPad side.
     */
    struct RawPacket {
        float x;            ///< Normalized X coordinate [0.0, 1.0]
        float y;            ///< Normalized Y coordinate [0.0, 1.0]
        float pressure;     ///< Normalized pressure [0.0, 1.0]
        uint8_t flags;      ///< Bitmask of Flags (e.g., DOWN, MOVE, UP)
        uint8_t padding[3]; ///< Padding for alignment
        uint64_t timestamp; ///< Timestamp in milliseconds since epoch
    };

    static_assert(sizeof(RawPacket) == 24, "InputPacket must be 24 bytes for protocol compatibility");
}