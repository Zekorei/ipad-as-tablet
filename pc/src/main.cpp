#include<iostream>
#include<winsock2.h>
#include<ws2tcpip.h>
#include<cstdint>

#include"input.h"
#include"protocol.h"

#pragma once
#pragma comment(lib, "ws2_32.lib")

// Constants
static const int PORT = 5000;
static const int BUFFER_SIZE = sizeof(InputPacket);

// Winsock init helper
bool initWinsock() {
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        std::cerr << "WSAStartup failed: " << result << std::endl;
        return false;
    }
    return true;
}

// Main
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

    while (true) {
        InputPacket packet;
        sockaddr_in clientAddr{};
        int clientSize = sizeof(clientAddr);

        int bytesReceived = recvfrom(
            sock,
            reinterpret_cast<char*>(&packet),
            BUFFER_SIZE,
            0,
            (sockaddr*)&clientAddr,
            &clientSize
        );

        if (bytesReceived == SOCKET_ERROR) {
            std::cerr << "recvfrom failed" << std::endl;
            continue;
        }

        // temporary debug
        // TODO: replace with queue
        // std::cout
        //     << "x: " << packet.x
        //     << " y: " << packet.y
        //     << " p: " << packet.pressure
        //     << " flags: " << (int)packet.flags
        //     << " ts: " << packet.timestamp
        //     << std::endl;
        moveMouse(packet.x, packet.y);
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}