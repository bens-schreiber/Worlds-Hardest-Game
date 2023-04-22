#pragma once

#include "raylib.h"
#include "Entity.hpp"
#include "const.h"

class Player : public Entity {

public:
	Player(): Entity({0,0},{playerSpeed,playerSpeed}),m_rectangle({0,0}) {}

	void draw() {
		DrawRectangle(this->m_position.x - (playerBorderSize/2), this->m_position.y - (playerBorderSize / 2), playerDimensions + playerBorderSize, playerDimensions + playerBorderSize, BLACK);
		m_rectangle.x = m_position.x;
		m_rectangle.y = m_position.y;
		m_rectangle.height = m_rectangle.width = playerDimensions;
		DrawRectangleRec(this->m_rectangle, RED);
	}


	void update() {

		if (IsKeyDown(KEY_D)) m_position.x += m_velocity.x;
		if (IsKeyDown(KEY_A)) m_position.x -= m_velocity.x;
		if (IsKeyDown(KEY_W)) m_position.y -= m_velocity.y;
		if (IsKeyDown(KEY_S)) m_position.y += m_velocity.y;

		// avoid going outside of bounds of map
	}

	void resetPosition() {
		this->m_position = { 0,0 };
	}

	Rectangle& getRectangle()
	{
		return m_rectangle;
	}

	int getDeaths() {
		return this->deaths;
	}

	void incrementDeaths() {
		this->deaths += 1;
	}

private:
	int deaths = 0;
	Rectangle m_rectangle;
};
