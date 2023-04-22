#pragma once
#include "Player.hpp"

class PlayerCollidable {
public:
	PlayerCollidable(Player* player) : m_player(player) {}

	virtual void handleCollision() = 0;

private:
	Player* m_player;
};
