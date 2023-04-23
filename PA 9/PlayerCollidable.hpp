#pragma once
#include "Player.hpp"
#include "PlayerDependency.hpp"

// Interface for dealing with player collisions
// Any class that implements PlayerCollidable will be able to collide with the player, and
// edit the players movement
class PlayerCollidable : protected PlayerDependency {
public:

	// Collide with player logic
	virtual void handlePlayerCollision(Rectangle rect) = 0;
};
