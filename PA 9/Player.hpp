#pragma once

#include "raylib.h"
#include "Entity.hpp"
#include "const.h"

class Player : public Entity {

public:
	Player(): Entity({0,0},{playerSpeed,playerSpeed}) {}

	void draw() {
		DrawRectangle(this->m_position.x-5, this->m_position.y-5, playerDimensions + 10, playerDimensions + 10, BLACK);
		DrawRectangle(this->m_position.x, this->m_position.y, playerDimensions, playerDimensions, RED);
	}


	void update() {

		if (IsKeyDown(KEY_D)) m_position.x += m_velocity.x;
		if (IsKeyDown(KEY_A)) m_position.x -= m_velocity.x;
		if (IsKeyDown(KEY_W)) m_position.y -= m_velocity.y;
		if (IsKeyDown(KEY_S)) m_position.y += m_velocity.y;

		// avoid going outside of bounds of map
	}

	void handleCollision(Entity* entity) {

	}


};
