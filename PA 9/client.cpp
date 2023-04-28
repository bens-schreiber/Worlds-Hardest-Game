#include "client.hpp"
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <thread>

SocketClient::SocketClient() : clientSocket(INVALID_SOCKET), clientThread() {}

void SocketClient::stopClient() {
    // Close the client socket
    closesocket(clientSocket);
    WSACleanup();

    killServer = true;
}

void SocketClient::clientThreadFunc() {
    while (!killServer) {
        runClientServer();
        std::this_thread::sleep_for(std::chrono::seconds(RETRY_CONN_WAIT));
        std::cout << "Retrying connection to server...\n";
    }
}

void SocketClient::runClientServer() {
    {
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            fprintf(stderr, "WSAStartup failed.\n");
            return;
        }

        struct addrinfo hints = { 0 };
        hints.ai_family = AF_INET; // use IPv4
        hints.ai_socktype = SOCK_STREAM; // use TCP
        hints.ai_protocol = IPPROTO_TCP; // use TCP

        struct addrinfo* result = NULL;
        int status = getaddrinfo(SERVER_ADDRESS, "http", &hints, &result);
        if (status != 0) {
            fprintf(stderr, "getaddrinfo failed: %d\n", status);
            WSACleanup();
            return;
        }

        SOCKET clientSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
        if (clientSocket == INVALID_SOCKET) {
            fprintf(stderr, "socket failed: %d\n", WSAGetLastError());
            freeaddrinfo(result);
            WSACleanup();
            return;
        }

        if (connect(clientSocket, result->ai_addr, (int)result->ai_addrlen) == SOCKET_ERROR) {
            fprintf(stderr, "connect failed: %d\n", WSAGetLastError());
            closesocket(clientSocket);
            freeaddrinfo(result);
            WSACleanup();
            return;
        }

        // For recieving info
        char buffer[BUFFER_SIZE];

        // For sending info
        std::stringstream ss;

        // Log connection
        std::cout << "Connection established to " << SERVER_ADDRESS << ":" << PORT_NUMBER << std::endl;

        while (1) {

            // new message
            ss.str("");
            ss << level << "," << position.x << "," << position.y;

            // send position message to the server
            send(clientSocket, ss.str().c_str(), ss.str().size(), 0);

            // get response
            int bytesRead = recv(clientSocket, buffer, BUFFER_SIZE - 1, 0);

            // Failed to get data
            if (bytesRead == SOCKET_ERROR) {
                closesocket(clientSocket);
                WSACleanup();
                std::cout << "Connection failed. Retrying..." << std::endl;
                return;
            }

            // append a nullchar to end 
            buffer[bytesRead] = '\0';

            // parse response
            if (mtx.try_lock()) {

                // No data
                if (buffer[0] == 'N') {
                    connectedPlayers.clear();
                }
                else {
                    SocketClientHelper::parseCsv(buffer, connectedPlayers);
                }
                mtx.unlock();
            }
        }

        // Close the client socket
        closesocket(clientSocket);
        WSACleanup();
    }
}