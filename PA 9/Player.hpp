#pragma once

#include "MapCollidable.hpp"
#include "Entity.hpp"
#include "consts.hpp"

// Main player of the game. Moveable via WASD keys.
// Injected into a singleton, grabbable via inheriting PlayerDependency
class Player : public Entity, public MapCollidable {
	float m_transperency = 1.0f;
	bool m_dead = false;
protected:

	int m_deaths = 0;

	// The current level the player is on
	int m_level = 0;

	// The spawnpoint the player will be reset at
	// Should be set after creating a map
	Vector2 m_spawnpoint;

	// Body
	Rectangle m_rectangle;

	// Movement locks for map collision
	bool canMoveRight = true;
	bool canMoveLeft = true;
	bool canMoveUp = true;
	bool canMoveDown = true;

public:

	// Determines if the player should go on to the next level or not
	bool levelCompleted = false;

	// Initialize player with spawnpoint (0,0)
	// X,Y velocity: playerSpeed
	// Rectangle: playerDimensions x playerDimensions
	 Player() : Entity(
		{ (screenWidth / 2)+1 ,(screenHeight / 2)+1 },
		{ playerSpeed,playerSpeed }),
		m_rectangle({ (screenWidth / 2)+1,(screenHeight / 2)+1, playerDimensions, playerDimensions }),
		m_spawnpoint({ (screenWidth / 2)+1,(screenHeight / 2)+1 })
	{}

	 // Reset movement locks
	 void resetMovement() {
		 canMoveRight = false;
		 canMoveLeft = false;
		 canMoveUp = false;
		 canMoveDown = false;
	 }

	// Draw the player body
	void draw() {

		if (m_dead)
		{
			m_transperency -= playerFadeoutRate;

			if (m_transperency <= 0)
			{
				m_transperency = 1.0f;
				resetPosition();
				m_dead = false;
			}
			resetMovement();
		}
		
		// BACKGROUND RECTANGLE
		DrawRectangle(
			m_position.x - (playerBorderSize/2),
			m_position.y - (playerBorderSize / 2), 
			playerDimensions + playerBorderSize, 
			playerDimensions + playerBorderSize, ColorAlpha(BLACK, m_transperency)
		);

		// PLAYER RECTANGLE
		DrawRectangleRec(m_rectangle, ColorAlpha(RED, m_transperency));
	}

	void killPlayer()
	{
		if (m_dead) {
			return;
		}
		m_dead = true;

		m_deaths++;
	}


	// Update movement via WASD keys by the vector velocity
	void update() {

		if (m_dead) {
			return;
		}
		// CONTROLS

		if (IsKeyDown(KEY_D) && canMoveRight) m_position.x += m_velocity.x;
		if (IsKeyDown(KEY_A) && canMoveLeft) m_position.x -= m_velocity.x;
		if (IsKeyDown(KEY_W) && canMoveUp) m_position.y -= m_velocity.y;
		if (IsKeyDown(KEY_S) && canMoveDown) m_position.y += m_velocity.y;

		// Set the player rectangle position
		m_rectangle.x = m_position.x;
		m_rectangle.y = m_position.y;
	}

	// Check every single component of the map against the player.
	// If the player can make a movement (UP, DOWN, RIGHT, LEFT) in the next frame (+ velocity) enable the movement
	// Else, the movement is already false.
	bool checkMapCollision(Rectangle rect) {

		if (!canMoveUp && CheckCollisionRecs({
			m_rectangle.x,
			m_rectangle.y - m_velocity.y - m_rectangle.height,
			m_rectangle.width,
			m_rectangle.height
			}, rect)) {
			canMoveUp = true;
		}

		if (!canMoveDown && CheckCollisionRecs({
			m_rectangle.x,
			m_rectangle.y + m_velocity.y + m_rectangle.height,
			m_rectangle.width,
			m_rectangle.height
			}, rect)) {
			canMoveDown = true;
		}

		if (!canMoveRight && CheckCollisionRecs({
			m_rectangle.x + m_velocity.x + m_rectangle.width,
			m_rectangle.y,
			m_rectangle.width,
			m_rectangle.height
			}, rect)) {
			canMoveRight = true;
		}

		if (!canMoveLeft && CheckCollisionRecs({
			m_rectangle.x - m_velocity.x - m_rectangle.width,
			m_rectangle.y,
			m_rectangle.width,
			m_rectangle.height
			}, rect)) {
			canMoveLeft = true;
		}

		return false;
	}

	// Handled in checkMapCollision
	void handleMapOutOfBounds() {}

	// Bring the player back to the spawnpoint
	void resetPosition() {
		m_position = m_spawnpoint; 

		// Set the player rectangle position
		m_rectangle.x = m_position.x;
		m_rectangle.y = m_position.y;
	}

	void setSpawnPoint(Vector2 spawnpoint) {
		m_position = spawnpoint;
		m_spawnpoint = spawnpoint;
	}

	const Rectangle& getRectangle() const {
		return m_rectangle;
	}

	int getDeaths() const {
		return m_deaths;
	}

	

	void incrementLevel() {
		m_level++;
	}

	int getLevel() {
		return m_level;
	}

};
