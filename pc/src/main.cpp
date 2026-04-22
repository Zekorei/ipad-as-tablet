#include<iostream>
#include<winsock2.h>
#include<ws2tcpip.h>
#include<cstdint>

#include"input.h"
#include"protocol.h"

#pragma comment(lib, "ws2_32.lib")

/// @brief UDP port number
constexpr int PORT = 5000;

/**
 * @brief Initialize Winsock.
 * 
 * @return true Success.
 * @return false Failure.
 */
bool initWinsock() {
    WSADATA wsaData;
    return WSAStartup(MAKEWORD(2, 2), &wsaData) == 0;
}

int main() {
    if (!initWinsock()) {
        return 1;
    }

    SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Failed to create socket" << std::endl;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sock, (sockaddr *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed" << std::endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    std::cout << "Listening on UDP port " << PORT << "..." << std::endl;

    bool mouseIsDown = false;

    while (true) {
        Protocol::InputPacket packet{};
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
            continue;
        }

        bool downEvent = (packet.flags & Protocol::DOWN) != 0;
        bool upEvent = (packet.flags & Protocol::UP) != 0;
        bool moveEvent = (packet.flags & Protocol::MOVE) != 0;

        if (moveEvent) {
            Input::moveMouse(packet.x, packet.y);
        }

        if (downEvent && !mouseIsDown) {
            Input::mouseDown();
            mouseIsDown = true;
        }
        
        if (upEvent && mouseIsDown) {
            Input::mouseUp();
            mouseIsDown = false;
        }
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}