#pragma once
#include "Player.hpp"

// Interface for dealing with player collisions
// Any class that implements PlayerCollidable will be able to collide with the player, and
// edit the players movement
class PlayerCollidable {
	static Player* m_player;

public:

	PlayerCollidable() = default;

	static void setPlayer(Player* player) {
		m_player = player;
	}

	// Collide with player logic
	virtual void handlePlayerCollision(Rectangle rect) = 0;

protected:
	Player& player() { 
		return *m_player; 
	}
};
