#pragma once

#include "raylib.h"
#include "Entity.hpp"
#include "consts.hpp"

// Main player of the game. Moveable via WASD keys.
class Player : public Entity {

	int m_deaths = 0;
	Vector2 m_spawnpoint;
	Rectangle m_rectangle;
	bool m_outOfBoundsR = false;
	bool m_outOfBoundsL = false;
	bool m_outOfBoundsUp = false;
	bool m_outOfBoundsDown = false;

public:

	// Initialize player with spawnpoint (0,0)
	// X,Y velocity: playerSpeed
	// Rectangle: playerDimensions x playerDimensions
	Player() : Entity(
		{ (screenWidth / 2)+1 ,(screenHeight / 2)+1 },
		{ playerSpeed,playerSpeed }),
		m_rectangle({ (screenWidth / 2)+1,(screenHeight / 2)+1, playerDimensions, playerDimensions }),
		m_spawnpoint({ (screenWidth / 2)+1,(screenHeight / 2)+1 })
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

		if (IsKeyDown(KEY_D) && !m_outOfBoundsR) m_position.x += m_velocity.x;
		if (IsKeyDown(KEY_A) && !m_outOfBoundsL) m_position.x -= m_velocity.x;
		if (IsKeyDown(KEY_W) && !m_outOfBoundsUp) m_position.y -= m_velocity.y;
		if (IsKeyDown(KEY_S) && !m_outOfBoundsDown) m_position.y += m_velocity.y;

		// Set the player rectangle position
		m_rectangle.x = m_position.x;
		m_rectangle.y = m_position.y;
	}

	void setOut_of_bounds_R(bool tf) {
		if (tf == true)
		{
			this->m_outOfBoundsR = true;
		}
		if (tf == false)
		{
			this->m_outOfBoundsR = false;
		}
	}


	void setOut_of_bounds_L(bool tf) {
		if (tf == true)
		{
			this->m_outOfBoundsL = true;
		}
		if (tf == false)
		{
			this->m_outOfBoundsL = false;
		}
	}

	void setOut_of_bounds_Up(bool tf) {
		if (tf == true)
		{
			this->m_outOfBoundsUp = true;
		}
		if (tf == false)
		{
			this->m_outOfBoundsUp = false;
		}
	}

	void setOut_of_bounds_Down(bool tf) {
		if (tf == true)
		{
			this->m_outOfBoundsDown = true;
		}
		if (tf == false)
		{
			this->m_outOfBoundsDown = false;
		}
	}

	// Bring the player back to the spawnpoint
	void resetPosition() {
		m_position = m_spawnpoint;
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
