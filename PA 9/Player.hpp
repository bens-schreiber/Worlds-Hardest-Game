#pragma once

#include "raylib.h"
#include "Entity.hpp"
#include "consts.hpp"

// Main player of the game. Moveable via WASD keys.
class Player : public Entity {

	int m_deaths = 0;
	Rectangle m_rectangle;

public:

	// Initialize player with spawnpoint (0,0)
	// X,Y velocity: playerSpeed
	// Rectangle: playerDimensions x playerDimensions
	Player() : Entity(
		{0,0},
		{playerSpeed,playerSpeed}), 
		m_rectangle({0,0, playerDimensions, playerDimensions})
	{}

	void draw() {

		// BACKGROUND RECTANGLE
		DrawRectangle(
			m_position.x - (playerBorderSize/2),
			m_position.y - (playerBorderSize / 2), 
			playerDimensions + playerBorderSize, 
			playerDimensions + playerBorderSize, BLACK
		);

		// PLAYER RECTANGLE
		DrawRectangleRec(m_rectangle, RED);
	}


	void update() {

		// CONTROLS
		if (IsKeyDown(KEY_D)) m_position.x += m_velocity.x;
		if (IsKeyDown(KEY_A)) m_position.x -= m_velocity.x;
		if (IsKeyDown(KEY_W)) m_position.y -= m_velocity.y;
		if (IsKeyDown(KEY_S)) m_position.y += m_velocity.y;

		// Set the player rectangle position
		m_rectangle.x = m_position.x;
		m_rectangle.y = m_position.y;
	}

	// Bring the player back to the spawnpoint
	void resetPosition() {
		m_position = { 0,0 };
	}

	// Return the player rectangle for collison calculations
	const Rectangle& getRectangle() const {
		return m_rectangle;
	}

	int getDeaths() const {
		return m_deaths;
	}

	void incrementDeaths() {
		m_deaths++;
	}
};
