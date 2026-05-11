#include"transport/packet_adapter.h"

#include<cmath>

namespace Input::Transport {

    std::optional<InputPacket> PacketAdapter::convert(const std::optional<Protocol::RawPacket>& raw) const {
        if (!isValid(raw)) {
            return std::nullopt;
        }

        Protocol::RawPacket packet = raw.value();

        return InputPacket{
            packet.x,
            packet.y,
            packet.pressure,
            packet.flags,
            packet.timestamp
        };
    }

    bool PacketAdapter::isValid(const std::optional<Protocol::RawPacket>& raw) const {
        // Has packet
        if (!raw.has_value()) {
            return false;
        }

        auto packet = raw.value();

        // Finite values
        if (!std::isfinite(packet.x) || !std::isfinite(packet.y)) {
            return false;
        }

        if (!std::isfinite(packet.pressure)) {
            return false;
        }

        if (!std::isfinite(packet.timestamp)) {
            return false;
        }

        // Bounds validation
        if (packet.pressure < 0.0f || packet.pressure > 1.0f) {
            return false;
        }

        return true;
    }
}