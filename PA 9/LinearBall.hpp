#pragma once

#include "Entity.hpp"
#include "consts.hpp"
#include "raylib.h"
#include "PlayerCollidable.hpp"

// Ball capable of moving linearly along the X or Y
class LinearBall : public Entity, public PlayerCollidable
{
public:

	LinearBall(Vector2 position, Vector2 velocity) : Entity(position, velocity), PlayerCollidable()
	{}

	void draw() {

		// BACKGROUND
		DrawCircle(m_position.x, m_position.y, radius, BLACK);

		// BALL
		DrawCircle(m_position.x, m_position.y, radius - 7, DARKBLUE);
	}
	void update() {

		// Increment the ball position in respect to its velocity
		m_position.x += m_velocity.x;
		m_position.y += m_velocity.y;

		if (m_position.y >= screenHeight - radius)
		{
			m_velocity.y *= -1; // change directions
		}
		if (m_position.y <= radius)
		{
			m_velocity.y *= -1;
		}
		if (m_position.x >= screenWidth - radius)
		{
			m_velocity.x *= -1;
		}
		if (m_position.x <= radius)
		{
			m_velocity.x *= -1;
		}
		handleCollision();
	}
	void handleCollision() {
		if (CheckCollisionCircleRec(m_position, radius, player().getRectangle()))
		{
			player().resetPosition();
		}
	}
};
