#pragma once

#include "raylib.h"
#include "Entity.hpp"
#include "consts.hpp"

// Main player of the game. Moveable via WASD keys.
class Player : public Entity {

	int m_deaths = 0;
	Vector2 m_spawnpoint;
	Rectangle m_rectangle;
	bool out_of_bounds_R = false;
	bool out_of_bounds_L = false;
	bool out_of_bounds_Up = false;
	bool out_of_bounds_Down = false;

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

		if (IsKeyDown(KEY_D) && !out_of_bounds_R) m_position.x += m_velocity.x;
		if (IsKeyDown(KEY_A) && !out_of_bounds_L) m_position.x -= m_velocity.x;
		if (IsKeyDown(KEY_W) && !out_of_bounds_Up) m_position.y -= m_velocity.y;
		if (IsKeyDown(KEY_S) && !out_of_bounds_Down) m_position.y += m_velocity.y;

		// Set the player rectangle position
		m_rectangle.x = m_position.x;
		m_rectangle.y = m_position.y;
	}

	void setOut_of_bounds_R(bool tf) {
		if (tf == true)
		{
			this->out_of_bounds_R = true;
		}
		if (tf == false)
		{
			this->out_of_bounds_R = false;
		}
	}


	void setOut_of_bounds_L(bool tf) {
		if (tf == true)
		{
			this->out_of_bounds_L = true;
		}
		if (tf == false)
		{
			this->out_of_bounds_L = false;
		}
	}

	void setOut_of_bounds_Up(bool tf) {
		if (tf == true)
		{
			this->out_of_bounds_Up = true;
		}
		if (tf == false)
		{
			this->out_of_bounds_Up = false;
		}
	}

	void setOut_of_bounds_Down(bool tf) {
		if (tf == true)
		{
			this->out_of_bounds_Down = true;
		}
		if (tf == false)
		{
			this->out_of_bounds_Down = false;
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
