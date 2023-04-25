#include "client.hpp"
#include "PlayerDependency.hpp"
class GhostPlayers : public FrameListenable, PlayerDependency {

	// Connection to the server
	static SocketClient* m_socketClient;

public:

	// Start socket connection
	GhostPlayers() {
		if (m_socketClient == nullptr) {
			m_socketClient = new SocketClient();
			m_socketClient->startClient();
		}
	}

	void update() {}

	// Draw the other players playing the game from the socket connection
	void draw() {
		m_socketClient->position = { player().getPosition().x , player().getPosition().y};
		if (m_socketClient->mutexLock) return;
		m_socketClient->mutexLock = true;
		for (const auto& i : m_socketClient->connectedPlayers) {
			DrawRectangle(i.x, i.y, playerDimensions, playerDimensions, PURPLE);
		}
		m_socketClient->mutexLock = false;
	}
};