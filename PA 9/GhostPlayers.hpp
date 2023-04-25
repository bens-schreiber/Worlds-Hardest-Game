#include "client.hpp"
#include "PlayerDependency.hpp"
class GhostPlayers : public FrameListenable, PlayerDependency {

	// Connection to the server
	static SocketClient* m_socketClient;
	std::vector<Coordinate> m_cachedPlayers;


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

		// Update position for socket client
		m_socketClient->position = { player().getPosition().x , player().getPosition().y};

		// Lock the mtx and draw if possible
		if (m_socketClient->mtx.try_lock()) {
			// Cache the connected players incase of mutex lock
			m_cachedPlayers = m_socketClient->connectedPlayers;

			for (const auto& i : m_socketClient->connectedPlayers) {
				DrawRectangle(i.x, i.y, playerDimensions, playerDimensions, PURPLE);
			}

			m_socketClient->mtx.unlock();
			return;
		}

		// Draw cached if mtx is locked
		for (const auto& i : m_cachedPlayers) {
			DrawRectangle(i.x, i.y, playerDimensions, playerDimensions, PURPLE);
		}
	}
};