#include "client.hpp"
#include "PlayerDependency.hpp"

// Manages a singleton SocketClient
// Draws all other connected players
class GhostPlayers : public FrameListenable, PlayerDependency {

	// Connection to the server
	static SocketClient* m_socketClient;

	// When in the middle of updating players (mutex lock enabled), we still need to draw players each frame.
	// Therefore, player coordinates are cached here incase of that scenario
	std::vector<Coordinate> m_cachedPlayers;

public:

	// Start socket connection
	GhostPlayers() {
		if (m_socketClient == nullptr) {
			m_socketClient = new SocketClient();
			m_socketClient->startClient();
		}
	}

	// Stop connection
	~GhostPlayers() {
		m_socketClient->stopClient();
	}

	void update() {}

	void drawGhost(Coordinate i) {

		// RECTANGLE
		DrawRectangle(i.x, i.y, ghostPlayerDimensions, ghostPlayerDimensions, ghostPlayerColor);
	}

	// Draw the other players playing the game from the socket connection
	void draw() {

		// Update level and position for socket client
		m_socketClient->position = { player().getPosition().x , player().getPosition().y};
		m_socketClient->level = player().getLevel();

		// Mutex will be locked if the connected players list is being updated.
		if (m_socketClient->mtx.try_lock()) {
			// Cache the connected players incase of mutex lock
			m_cachedPlayers = m_socketClient->connectedPlayers;

			for (const auto& i : m_socketClient->connectedPlayers) drawGhost(i);

			m_socketClient->mtx.unlock();
			return;
		}

		// Draw using cached if mtx is locked
		for (const auto& i : m_cachedPlayers) drawGhost(i);
	}
};