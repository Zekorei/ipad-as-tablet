#pragma once

#include<optional>
#include<cstdint>

#include"shared/protocol.h"

#ifdef _WIN32
#include<winsock2.h>
#endif

namespace Input::Transport {

    /**
     * @brief UDP receiver that extracts a raw packet from the given port and returns an optional raw packet. Ensures only well-formed
     * packets are delivered to the rest of the pipeline while invalid ones are dropped.
     * 
     */
    class UDPReceiver {
    public:
        explicit UDPReceiver(uint16_t port);
        ~UDPReceiver();

        // non-copyable
        UDPReceiver(const UDPReceiver&) = delete;
        UDPReceiver& operator=(const UDPReceiver&) = delete;

        /**
         * @brief Receives a packet from the assigned UDP port.
         * 
         * @return std::optional<Protocol::RawPacket> Returns a raw pack if and only if it is well-formed.
         */
        std::optional<Protocol::RawPacket> receive();
    private:
#ifdef _WIN32
        SOCKET sock = INVALID_SOCKET;
#endif

        void initialize(uint16_t port);
        void cleanup();
    };
}
