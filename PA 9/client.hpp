#pragma once
#include <vector>
#include <thread>
#include <string>
#include <iostream>
#include <sstream>
#include <mutex>

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)
#define BUFFER_SIZE 1024
#define SERVER_ADDRESS "127.0.0.1"
#define PORT_NUMBER 8080

// DISCLAIMER:
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

    // Data will be coming in the form "x,y x,y x,y x,y"
    // parse this to a coordinate list
    static void parseCsv(char* input, std::vector<Coordinate>& coordinates) {
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

// Manages connection to the external server
class SocketClient {

    // Winsock2 socket
    SOCKET clientSocket;

    // Thread for handling the SocketClient
    std::thread clientThread;

    // Function to be called on loop in the thread
    void clientThreadFunc();

public:

    // All player coordinates sent by the server at any given frame/
    // Be cautious when using, wrap in a try_mutex
    std::mutex mtx;
    std::vector<Coordinate> connectedPlayers = {};

    // The position of the games current player. 
    // Cannot make this class a player dependency because the raylib library has issues with Winsock2
    Coordinate position = { 0,0 };

    // Level of the games current player
    int level = 0;

    SocketClient();

    // Stop the client 
    ~SocketClient() {
        stopClient();
    }

    // Begin the server on a seperate detatched thread. Must be closed manually.
    void startClient() {
        // Start a new thread for the client connection
        clientThread = std::thread(&SocketClient::clientThreadFunc, this);
        clientThread.detach(); // Detach the thread so it can run independently
    }

    void stopClient();
};



