#include "client.hpp"
#include <WinSock2.h>
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
        std::this_thread::sleep_for(std::chrono::seconds(RETRY_CONN_WAIT));
        std::cout << "Retrying connection to server...\n";
        runClientServer();
    }
}

void SocketClient::runClientServer() {
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