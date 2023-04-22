#pragma once
#include "PlayerCollidable.hpp"
#include "const.h"
#include <vector>
#include "raylib.h"

class Map : public PlayerCollidable {
	std::vector<Rectangle> m_components;

public:
	Map(Player* player) : PlayerCollidable(player) {}


};
