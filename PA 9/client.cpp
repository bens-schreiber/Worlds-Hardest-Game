#include "client.hpp"
#include <WinSock2.h>

SocketClient::SocketClient() : clientSocket(INVALID_SOCKET), clientThread() {}

void SocketClient::stopClient() {
    // Close the client socket
    closesocket(clientSocket);
    WSACleanup();

    // Join the client thread if it's joinable
    if (clientThread.joinable()) {
        clientThread.join();
    }
}

void SocketClient::clientThreadFunc() {
    {
        WSADATA wsaData;

        // Server didn't start
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) return;

        clientSocket = socket(AF_INET, SOCK_STREAM, 0);

        // Failed to initialize socket
        if (clientSocket == INVALID_SOCKET) {
            WSACleanup();
            return;
        }

        struct sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(PORT_NUMBER);
        serverAddr.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);

        // Failed to connect
        if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
            closesocket(clientSocket);
            WSACleanup();
            return;
        }

        char buffer[BUFFER_SIZE];
        std::stringstream ss;
        ss << "5,3";
        std::string msg = ss.str();

        while (1) {
            if (mutexLock) continue;
            send(clientSocket, msg.c_str(), msg.size(), 0);
            int bytesRead = recv(clientSocket, buffer, BUFFER_SIZE - 1, 0);

            // Failed to get data
            if (bytesRead == SOCKET_ERROR) {
                closesocket(clientSocket);
                WSACleanup();
                return;
            }

            buffer[bytesRead] = '\0';

            SocketClient::mutexLock = true;
            SocketClientHelper::parseJson(buffer, connectedPlayers);
            SocketClient::mutexLock = false;
        }

        // Close the client socket
        closesocket(clientSocket);
        WSACleanup();
    }
}