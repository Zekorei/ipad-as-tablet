#pragma once

#include <optional>

#include "types/input_packet.h"
#include "protocol.h"

namespace Input::Transport {

    /** 
     * @brief Validates an input packet. Also passes on invalid packets as an optional through the pipeline.
     */
    class PacketAdapter {
    public:
        /**
         * @brief Converts a raw packet to an input packet while validating its contents.
         * 
         * @param raw The raw input packet received over protocol.
         * @return std::optional<Input::InputPacket> 
         */
        std::optional<InputPacket> convert(const std::optional<Protocol::RawPacket>& raw) const;
    
    private:
        bool isValid(const std::optional<Protocol::RawPacket>& raw) const;
    };
}
