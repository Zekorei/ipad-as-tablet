#include"transport/udp_receiver.h" 

#include<iostream>
#include<cstring>

#ifdef _WIN32
#include<ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#endif

namespace Input::Transport {
    
    UDPReceiver::UDPReceiver(uint16_t port) {
        initialize(port);
    }

    UDPReceiver::~UDPReceiver() {
        cleanup();
    }

    void UDPReceiver::initialize(uint16_t port) {
#ifdef _WIN32
        WSADATA wsaData;

        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            throw std::runtime_error("WSAStartup() failed");
        }

        sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

        if (sock == INVALID_SOCKET) {
            throw std::runtime_error("Failed to create socket");
        }

        sockaddr_in serverAddr{};
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(port);
        serverAddr.sin_addr.s_addr = INADDR_ANY;

        if (bind(sock, (sockaddr *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
            throw std::runtime_error("bind() failed");
        }

        std::cout << "Listening on UDP port " << port << "..." << std::endl;
#endif
    }

    void UDPReceiver::cleanup() {
#ifdef _WIN32
        if (sock != INVALID_SOCKET) {
            closesocket(sock);
        }

        WSACleanup();
#endif
    }

    std::optional<Protocol::RawPacket> UDPReceiver::receive() {
#ifdef _WIN32
        Protocol::RawPacket packet{};
        sockaddr_in clientAddr{};
        int clientSize = sizeof(clientAddr);

        int bytesReceived = recvfrom(
            sock,
            reinterpret_cast<char*>(&packet),
            sizeof(packet),
            0,
            (sockaddr*)&clientAddr,
            &clientSize
        );

        if (bytesReceived == SOCKET_ERROR) {
            std::cerr << "recvfrom failed" << std::endl;
            return std::nullopt;
        }

        if (bytesReceived != sizeof(Protocol::RawPacket)) {
            return std::nullopt; // partial or malformed packet
        }

        return packet;
#endif
        return std::nullopt;
    }
}
