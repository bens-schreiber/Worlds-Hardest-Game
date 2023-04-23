#pragma once

#include "Entity.hpp"
#include "consts.hpp"
#include "raylib.h"
#include "PlayerCollidable.hpp"

// Ball capable of moving linearly along the X or Y
class LinearBall : public Entity, PlayerCollidable
{
public:

	LinearBall(Vector2 position, Vector2 velocity) : Entity(position, velocity)
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
			flipVelocityY();
		}
		if (m_position.y <= ballRadius + interfaceBarHeight)
		{
			flipVelocityY();
		}
		if (m_position.x >= screenWidth - ballRadius)
		{
			flipVelocityX();
		}
		if (m_position.x <= ballRadius)
		{
			flipVelocityX();
		}

		handlePlayerCollision();
	}
	void handlePlayerCollision(Rectangle rect = {}) {

		// If the ball and the player collide
		if (CheckCollisionCircleRec(m_position, ballRadius, player().getRectangle()))
		{
			player().resetPosition();
			player().incrementDeaths();
		}
	}
};
