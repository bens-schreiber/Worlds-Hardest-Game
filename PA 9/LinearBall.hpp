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
		DrawCircle(m_position.x, m_position.y, ballRadius, BLACK);

		// BALL
		DrawCircle(m_position.x, m_position.y, ballRadius - 7, DARKBLUE);
	}
	void update() {

		// Increment the ball position in respect to its velocity
		m_position.x += m_velocity.x;
		m_position.y += m_velocity.y;

		if (m_position.y >= screenHeight - ballRadius - interfaceBarHeight)
		{
			m_velocity.y *= -1; // change directions
		}
		if (m_position.y <= ballRadius + interfaceBarHeight)
		{
			m_velocity.y *= -1;
		}
		if (m_position.x >= screenWidth - ballRadius)
		{
			m_velocity.x *= -1;
		}
		if (m_position.x <= ballRadius)
		{
			m_velocity.x *= -1;
		}
		handleCollision();
	}
	void handleCollision() {
		if (CheckCollisionCircleRec(m_position, ballRadius, player().getRectangle()))
		{
			player().resetPosition();
		}
	}
};
