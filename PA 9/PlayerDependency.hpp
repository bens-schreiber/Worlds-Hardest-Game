#pragma once
#include "Player.hpp"

// Dependency injection for getting the Player
class PlayerDependency{
	static Player* m_player;

public:

	static Player* newPlayer() {
		m_player = new Player();
		return m_player;
	}

	static void setPlayer(Player* player) {
		m_player = player;
	}

protected:
	Player& player() {
		return *m_player;
	}

	Player* playerPointer() {
		return m_player;
	}
};
