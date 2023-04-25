#pragma once
#include <vector>
#include <thread>
#include <string>
#include <iostream>
#include <sstream>

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)
#define BUFFER_SIZE 1024
#define SERVER_ADDRESS "127.0.0.1"
#define PORT_NUMBER 8080

// Winsock2 defines some functions that are also in raylib
// Have to jump through some hurdles with defining the library only in the client.cpp file
typedef unsigned __int64 SOCKET;

// Struct to represent a coordinate
struct Coordinate {
    float x;
    float y;
};

class SocketClientHelper {
    friend class SocketClient;
    static void parseJson(char* input, std::vector<Coordinate>& coordinates) {
        if (input == nullptr) return;
        coordinates = {};
        std::istringstream iss(input);
        std::string coordinateString;
        while (std::getline(iss, coordinateString, ' ')) {
            size_t commaPos = coordinateString.find(',');
            float x = std::stof(coordinateString.substr(0, commaPos));
            float y = std::stof(coordinateString.substr(commaPos + 1));
            coordinates.push_back({ x, y });
        }
    }
};

class SocketClient {
public:

    std::vector<Coordinate> connectedPlayers = {};
    bool mutexLock = false;
    Coordinate position = { 0,0 };

    SocketClient();

    ~SocketClient() {
        stopClient();
    }

    void startClient() {
        // Start a new thread for the client connection
        clientThread = std::thread(&SocketClient::clientThreadFunc, this);
        clientThread.detach(); // Detach the thread so it can run independently
    }

    void stopClient();

private:
    SOCKET clientSocket;
    std::thread clientThread;

    void clientThreadFunc();
};



