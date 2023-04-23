#pragma once
#include "Player.hpp"

// Dependency injection for using getting the Player
class PlayerDependency{
	static Player* m_player;

public:

	PlayerDependency() = default;

	static void setPlayer(Player* player) {
		m_player = player;
	}

protected:
	Player& player() {
		return *m_player;
	}
};
