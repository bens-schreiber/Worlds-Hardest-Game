#pragma once
#include "Player.hpp"

// Interface for dealing with player collisions
// Any class that implements PlayerCollidable will be able to collide with the player, and
// edit the players movement
class PlayerCollidable {
public:
	PlayerCollidable(Player* player) : m_player(player) {}

	// Collide with player logic
	virtual void handleCollision() = 0;

protected:
	Player* m_player;
};
